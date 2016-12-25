//
//  RequestHandler.h
//  csaw
//
//  Created by Steve on 24/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#ifndef RequestHandler_h
#define RequestHandler_h

class IRequestHandler {
public:
    virtual ~IRequestHandler () {};
    virtual void DoRequest (int id) = 0;
};

#endif /* RequestHandler_h */

