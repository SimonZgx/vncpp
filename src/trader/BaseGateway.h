//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BASEGATEWAY_H
#define MAIN_BASEGATEWAY_H



class BaseGateway {
private:
	void OnOrder();
	virtual void Connect()=0;
	virtual void SendOrder()=0;
};


#endif //MAIN_BASEGATEWAY_H
