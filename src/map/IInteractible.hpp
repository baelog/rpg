
#ifndef IINTERACTIBLE_H_
#define IINTERACTIBLE_H_

#include "IObject.hpp"

/**
 * type 0 get
 * type 1 put
 * type 2 passif
 */

//TODO it will become a colider object
struct IInteractible : public IObject {
    private:
        int _type;
        
    public:

        virtual int getType() const = 0;
        // void (*move)(struct my_s*);
};

#endif 