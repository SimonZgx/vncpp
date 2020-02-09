//
// Created by Simon on 2020/2/9.
//
#include <iostream>
#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

int main(){
    boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
    std::string uuid_string = boost::uuids::to_string(a_uuid);
    std::cout<<uuid_string<<std::endl;
    return 0;
}