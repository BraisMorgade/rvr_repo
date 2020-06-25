#include "NetMessage.h"

void NetMessage::to_bin(){
    
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    char* tmp = _data;

    memcpy(tmp, &type, sizeof(u_int8_t));
    tmp+=sizeof(u_int8_t);

    memcpy(tmp, message, sizeof(char)*80);
    /*
    memcpy(tmp, &inputs.left, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(tmp, &inputs.right, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(tmp, &inputs.up, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(tmp, &inputs.down, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(tmp, &inputs.atk, sizeof(bool));
    */
}

int NetMessage::from_bin(char* bobj){
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);

    char* tmp = _data;

    memcpy(&type, tmp, sizeof(u_int8_t));
    tmp+=sizeof(u_int8_t);

    free(message);
    message=(char*)malloc(sizeof(char)*82);

    memcpy(message, tmp, sizeof(char)*80);
    /*
    memcpy(&inputs.left,tmp, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(&inputs.right,tmp, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(&inputs.up, tmp, sizeof(bool));
    tmp+=sizeof(bool);

    memcpy(&inputs.down, tmp,sizeof(bool));
    tmp+=sizeof(bool);

    memcpy( &inputs.atk,tmp, sizeof(bool));
    */


}