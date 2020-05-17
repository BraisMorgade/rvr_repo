#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

class Jugador : public Serializable
{
public:
    Jugador(const char* _n, int16_t _x, int16_t _y) :x(_x), y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador() {};

    void to_bin()
    {
        int32_t total = 80 * sizeof(char) + 2 * sizeof(int16_t);

        alloc_data(total);

        char* tmp = _data;

        memcpy(tmp, name, 80);
        tmp += 80 * sizeof(char);

        memcpy(tmp, &x, sizeof(int16_t));
        tmp += sizeof(int16_t);

        memcpy(tmp, &y, sizeof(int16_t));
    }

    int from_bin(char* data)
    {

        alloc_data(80 * sizeof(char) + 2 * sizeof(int16_t));

        char* tmp = data;

        memcpy(name, tmp, 80);
        tmp += 80 * sizeof(char);


        memcpy(&x, tmp, sizeof(int16_t));
        tmp += sizeof(int16_t);

        memcpy(&y, tmp, sizeof(int16_t));


        return 0;
    }

public:
    char name[80];

    int16_t x;
    int16_t y;
};

int main(int argc, char** argv)
{
    Jugador one_r("", 0, 0);
    Jugador one_w("Player_ONE", 123, 987);

    one_w.to_bin();

    std::ofstream file("jugador.bin");
    std::fstream fs;
    fs.open("jugador.bin");
    fs.write(one_w.data(), one_w.size());
    fs.close();


    char* a = (char*)malloc(one_w.size());
    fs.open("jugador.bin");
    fs.read(a, one_w.size());
    fs.close();
    one_r.from_bin(a);

    std::cout << "name: " << one_r.name << " x: " << one_r.x << " y: " << one_r.y << "\n";

    return 0;
}