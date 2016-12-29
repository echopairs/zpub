//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_STATUS_H
#define ZPUB_STATUS_H

namespace nsky {

    enum StatusCode {
        /// Not an error; return on success
                OK = 0,

        /// Error
                ERROR = 1,
        /// The operation was cancelled
                CANCELLED = 2

        /// here to add error code
    };
}
#endif //ZPUB_STATUS_H
