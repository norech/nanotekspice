#include "Components.hpp"

namespace nts
{
    Component4001::Component4001(const std::string& name) : Component(name)
    {
        for (int i = 0; i < 4; i++) _nors[i] = std::make_unique<Nor>();

        addInputPin(1).addInputPin(2).addOutputPin(3)
            .addOutputPin(4).addInputPin(5).addOutputPin(6)
            .addInputPin(8).addInputPin(9).addOutputPin(10)
            .addOutputPin(11).addInputPin(12).addInputPin(13);

        this->setLink(1, *_nors[0], 1);
        this->setLink(2, *_nors[0], 2);
        this->setLink(3, *_nors[0], 3);

        this->setLink(4, *_nors[1], 3);
        this->setLink(5, *_nors[1], 1);
        this->setLink(6, *_nors[1], 2);

        this->setLink(8, *_nors[2], 2);
        this->setLink(9, *_nors[2], 1);
        this->setLink(10, *_nors[2], 3);

        this->setLink(11, *_nors[3], 3);
        this->setLink(12, *_nors[3], 2);
        this->setLink(13, *_nors[3], 1);
    }

    Component4081::Component4081(const std::string& name) : Component(name)
    {
        for (int i = 0; i < 4; i++) _and[i] = std::make_unique<And>();

        addInputPin(1).addInputPin(2).addOutputPin(3)
            .addOutputPin(4).addInputPin(5).addOutputPin(6)
            .addInputPin(8).addInputPin(9).addOutputPin(10)
            .addOutputPin(11).addInputPin(12).addInputPin(13);

        this->setLink(1, *_and[0], 1);
        this->setLink(2, *_and[0], 2);
        this->setLink(3, *_and[0], 3);

        this->setLink(4, *_and[1], 3);
        this->setLink(5, *_and[1], 1);
        this->setLink(6, *_and[1], 2);

        this->setLink(8, *_and[2], 2);
        this->setLink(9, *_and[2], 1);
        this->setLink(10, *_and[2], 3);

        this->setLink(11, *_and[3], 3);
        this->setLink(12, *_and[3], 2);
        this->setLink(13, *_and[3], 1);
    }

}
