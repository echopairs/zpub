//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_STATUS_CODE_ENUM_H
#define ZPUB_STATUS_CODE_ENUM_H
#include <nsky/utils/status.h>
#include <string>

namespace  nsky {
    /// Did it work ? If it didn't, way?
    class Status
    {
    public:
        Status():_code(StatusCode::OK){}
        Status(StatusCode _code, const std::string &_details) : _code(_code), _details(_details) { }
    public:
        const std::string &get_details() const
        {
            return _details;
        }

        void set_details(const std::string &_details)
        {
            Status::_details = _details;
        }

        StatusCode get_code() const
        {
            return _code;
        }


        void set_code(StatusCode _code)
        {
            Status::_code = _code;
        }

        /// Is the status OK?
        bool Ok() const { return _code == StatusCode::OK;}

        /// Pre-defined special status objects.
        /// An OK pre-defined instance.
        static const Status &OK;

    private:
        StatusCode _code;
        std::string _details;
    };

}
#endif //ZPUB_STATUS_CODE_ENUM_H
