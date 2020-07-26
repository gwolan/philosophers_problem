#include <Miscellanous/Dice.hpp>


Dice::Dice(uint32_t lowerBound, uint32_t upperBound)
    : randomDevice()
    , randomEngine(randomDevice())
    , unsignedUniformIntDistribution(lowerBound, upperBound)
    , signedUniformIntDistribution(lowerBound, upperBound)
{ }

uint32_t Dice::rollUnsignedInt()
{
    return unsignedUniformIntDistribution(randomEngine);
}

int32_t Dice::rollSignedInt()
{
    return signedUniformIntDistribution(randomEngine);
}
