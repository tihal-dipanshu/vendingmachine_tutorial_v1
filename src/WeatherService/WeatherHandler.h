#ifndef VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/WeatherService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class WeatherServiceHandler : public WeatherServiceIf {
 public:
  WeatherServiceHandler();
  ~WeatherServiceHandler() override=default;

  WeatherType::type GetWeather(const int64_t city) override;
};

// Constructor
WeatherServiceHandler::WeatherServiceHandler() {

}

// Remote Procedure "PlaceOrder"

WeatherType::type WeatherServiceHandler::GetWeather(const int64_t city) {
     // Your implementation goes here
     printf("GetWeather\n");

    // Replace random logic with odd-even check
    if (city % 2 == 1) {
        return WeatherType::WARM;
    } else {
        return WeatherType::COLD;
    }
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H

