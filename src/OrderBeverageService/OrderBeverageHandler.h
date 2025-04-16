#ifndef VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/OrderBeverageService.h"
#include "../../gen-cpp/WeatherService.h"
#include "../../gen-cpp/BeveragePreferenceService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class OrderBeverageServiceHandler : public OrderBeverageServiceIf {
 public:
  OrderBeverageServiceHandler(
      ClientPool<ThriftClient<WeatherServiceClient>> *,
      ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *);
  ~OrderBeverageServiceHandler() override=default;

  void PlaceOrder(std::string& _return, const int64_t city) override;
 private:
  ClientPool<ThriftClient<WeatherServiceClient>> *_weather_client_pool;
  ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *_beverage_client_pool;
};

// Constructor
OrderBeverageServiceHandler::OrderBeverageServiceHandler(
    ClientPool<ThriftClient<WeatherServiceClient>> *weather_client_pool,
    ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *beverage_client_pool) {
     // Storing the clientpools
     _weather_client_pool = weather_client_pool;
     _beverage_client_pool = beverage_client_pool;
}

// Remote Procedure "PlaceOrder"
void OrderBeverageServiceHandler::PlaceOrder(std::string& _return, const int64_t city) {
     // Your implementation goes here
     printf("PlaceOrder\n");

     // Get weather service client
     auto weather_client_wrapper = _weather_client_pool->Pop();
     if (!weather_client_wrapper) {
       ServiceException se;
       se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
       se.message = "Failed to connect to weather-service";
       throw se;
     }
     auto weather_client = weather_client_wrapper->GetClient();

     // Get weather
     WeatherType::type weather;
     try {
       weather = weather_client->GetWeather(city);
     } catch (...) {
       _weather_client_pool->Push(weather_client_wrapper);
       ServiceException se;
       se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
       se.message = "Failed to get weather from weather-service";
       throw se;
     }
     _weather_client_pool->Push(weather_client_wrapper);

     // Determine beverage type
     BeverageType::type btype = (weather == WeatherType::WARM) ? 
       BeverageType::HOT : BeverageType::COLD;

     // Get beverage service client
     auto beverage_client_wrapper = _beverage_client_pool->Pop();
     if (!beverage_client_wrapper) {
       ServiceException se;
       se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
       se.message = "Failed to connect to beverage-preference-service";
       throw se;
     }
     auto beverage_client = beverage_client_wrapper->GetClient();

     // Get beverage
     std::string beverage;
     try {
       beverage_client->PlaceOrder(beverage, btype);
     } catch (...) {
       _beverage_client_pool->Push(beverage_client_wrapper);
       ServiceException se;
       se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
       se.message = "Failed to get beverage from beverage-preference-service";
       throw se;
     }
     _beverage_client_pool->Push(beverage_client_wrapper);

     _return = "City ID: " + std::to_string(city) + ", Beverage: " + beverage;
}

} // namespace vending_machine

#endif //VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

