#include "Chat.h"

void ChatMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    char* tmp = _data;

    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    const char* n = nick.c_str();
    memcpy(tmp, n, sizeof(char) * 8);

    tmp += sizeof(char) * 8;

    const char* m = message.c_str();
    memcpy(tmp, m, sizeof(char) * 80);
}

int ChatMessage::from_bin(char* bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);

    char* tmp = _data;

    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    nick = std::string(tmp);
    tmp += sizeof(char) * 8;

    message = std::string(tmp);

    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatServer::do_messages()
{
    while (true)
    {
        Socket* client;
        ChatMessage message;
        int r = socket.recv(message, client);
        if (r != 0) continue;
        switch (message.type) {
        case ChatMessage::LOGIN:
            clients.push_back(client);
            break;
        case ChatMessage::LOGOUT:
            for (int i = 0; i < clients.size(); i++) {
                if (*clients[i] == *client) {
                    clients.erase(clients.begin() + i);
                    break;
                }
            }
            break;
        case ChatMessage::MESSAGE:
            for (int i = 0; i < clients.size(); i++) {
                if (!(*clients[i] == *client)) {
                    socket.send(message, *clients[i]);
                }
            }
            break;
        default:
            break;
        }
    }
}

void ChatClient::login()
{
    std::string msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGIN;

    socket.send(em, socket);
}

void ChatClient::logout()
{
    std::string msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGOUT;

    socket.send(em, socket);
}

void ChatClient::input_thread()
{
    while (true)
    {
        std::string msg;
        std::getline(std::cin, msg);

        ChatMessage m(nick, msg);
        m.type = ChatMessage::MESSAGE;

        socket.send(m, socket);
    }
}

void ChatClient::net_thread()
{
    while (true)
    {
        ChatMessage message;
        int r = socket.recv(message);
        if (r != 0) continue;
        if (message.type == ChatMessage::MESSAGE) {
            std::cout << message.nick << ": " << message.message << "\n";
        }
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
    }
}
