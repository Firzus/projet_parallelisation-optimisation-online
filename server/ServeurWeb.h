#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class ServeurWeb {
private:
	SOCKET Sock;


	ServeurWeb();
	virtual ~ServeurWeb();
	void Init(ServeurWeb S);
	void ProtoHTTP();
};
