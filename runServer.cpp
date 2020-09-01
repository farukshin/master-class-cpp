#include <iostream>
#include<uwebsockets/App.h>
#include <thread>
#include <vector>
#include<algorithm>

using namespace std;

struct UserConnection {
    
    unsigned long used_id;
    string* user_name;
    
};

int main()
{
    atomic_ulong latest_user_id = 10;

    vector<thread*> threads(thread::hardware_concurrency());
    
    transform(threads.begin(), threads.end(), threads.begin(), [&latest_user_id](auto* thr) {
        return new thread([&latest_user_id]() {
            uWS::App().ws<UserConnection>("/*", {
                .open = [&latest_user_id](auto* ws) {
                    // что делать при подключении пользователя
                    UserConnection* data = (UserConnection*)ws->getUserData();
                    data->used_id = latest_user_id++;
                    cout << "new user id " << data->used_id <<  endl;
                    ws->subscribe("broadcast");
                    ws->subscribe("user#" + to_string(data->used_id));
                },

                .message = [&](auto* ws, string_view message, uWS::OpCode) {
                    // что делать при получении сообщения
                    UserConnection* data = (UserConnection*)ws->getUserData();
                    cout << "New message " << message << "UserId = "<< data->used_id <<endl;
                    auto begining = message.substr(0, 9);
                    if (begining.compare("SETNAME=") == 0) {
                        //  пользователь прислал свое имя
                        auto name = message.substr(9);
                        data->user_name = new string(name);
                        cout << "User set their name ID =" << data->used_id << " name = " << (*data->user_name) << endl;
                        string broadcast_message = format("NEWUSER,{},{}", (*data->user_name), data->used_id);
                        ws->publish("broadcast", broadcast_message, opCode,  )
                    }
                    auto is_message_to = message.substr(0, 11);
                    if (is_message_to.compare("MESSAGETO=") == 0) {
                        // кто-то послал сообщение
                        auto rest = message.substr(11);
                        int position = rest.find(",");
                        if (position != -1)
                            auto id = rest.substr(0, position);
                            auto user_message  = rest.substr(position+1);
                            ws->publish("user#"+to_string(data->used_id), user_message, opCode, false)
                    }
                }

                }).listen(9999, [&](auto* token) {
                    if(token)
                        cout << "server started and listening on port 9999" << endl;
                    else cout << "server failed to start" << endl;
                    }).run();
            
            })

        });


    for_each (threads.begin(), threads.end(), threads.begin(), [](auto* thr) {thr->join();});

    
}
