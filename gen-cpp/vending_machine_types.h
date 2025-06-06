/**
 * Autogenerated by Thrift Compiler (0.21.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef vending_machine_TYPES_H
#define vending_machine_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>


namespace vending_machine {

struct ErrorCode {
  enum type {
    SE_CONNPOOL_TIMEOUT = 0,
    SE_THRIFT_CONN_ERROR = 1,
    SE_UNAUTHORIZED = 2,
    SE_MEMCACHED_ERROR = 3,
    SE_MONGODB_ERROR = 4,
    SE_REDIS_ERROR = 5,
    SE_THRIFT_HANDLER_ERROR = 6,
    SE_RABBITMQ_CONN_ERROR = 7
  };
};

extern const std::map<int, const char*> _ErrorCode_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const ErrorCode::type& val);

std::string to_string(const ErrorCode::type& val);

struct WeatherType {
  enum type {
    WARM = 0,
    COLD = 1
  };
};

extern const std::map<int, const char*> _WeatherType_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const WeatherType::type& val);

std::string to_string(const WeatherType::type& val);

struct BeverageType {
  enum type {
    HOT = 0,
    COLD = 1
  };
};

extern const std::map<int, const char*> _BeverageType_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const BeverageType::type& val);

std::string to_string(const BeverageType::type& val);

class ServiceException;

class location;

typedef struct _ServiceException__isset {
  _ServiceException__isset() : errorCode(false), message(false) {}
  bool errorCode :1;
  bool message :1;
} _ServiceException__isset;

class ServiceException : public ::apache::thrift::TException {
 public:

  ServiceException(const ServiceException&);
  ServiceException& operator=(const ServiceException&);
  ServiceException() noexcept;

  virtual ~ServiceException() noexcept;
  /**
   * 
   * @see ErrorCode
   */
  ErrorCode::type errorCode;
  std::string message;

  _ServiceException__isset __isset;

  void __set_errorCode(const ErrorCode::type val);

  void __set_message(const std::string& val);

  bool operator == (const ServiceException & rhs) const;
  bool operator != (const ServiceException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ServiceException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept override;
};

void swap(ServiceException &a, ServiceException &b);

std::ostream& operator<<(std::ostream& out, const ServiceException& obj);

typedef struct _location__isset {
  _location__isset() : location_id(false), city(false) {}
  bool location_id :1;
  bool city :1;
} _location__isset;

class location : public virtual ::apache::thrift::TBase {
 public:

  location(const location&) noexcept;
  location& operator=(const location&) noexcept;
  location() noexcept;

  virtual ~location() noexcept;
  int64_t location_id;
  int64_t city;

  _location__isset __isset;

  void __set_location_id(const int64_t val);

  void __set_city(const int64_t val);

  bool operator == (const location & rhs) const;
  bool operator != (const location &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const location & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(location &a, location &b);

std::ostream& operator<<(std::ostream& out, const location& obj);

} // namespace

#endif
