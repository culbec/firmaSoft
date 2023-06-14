#pragma once

class Observer{
public:
    /*
     * Updateaza observer-ul
     */
    virtual void update() = 0;

    /*
     * destructor
     */
    virtual ~Observer() = default;
};