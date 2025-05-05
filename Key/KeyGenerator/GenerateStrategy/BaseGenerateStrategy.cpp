#include "BaseGenerateStrategy.h"

#include <QRandomGenerator>

constexpr const quint32 PUBLIC_PART_LEN     { 512u / 8u };
constexpr const quint32 PRIVATE_PART_LEN    { 256 / 8u };

template<typename T>
T getRandomBoundedNumber()
{
    return QRandomGenerator::global()->bounded(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

BaseGenerateStrategy::BaseGenerateStrategy()
    : AKeyGenerateStrategy { AKeyGenerator::KeyGeneratorAlgorithm::BASE }
{

}

QByteArray BaseGenerateStrategy::generatePublicKey(const QByteArray &privateKey) const
{
    Q_ASSERT(privateKey.size() == PRIVATE_PART_LEN);

    QByteArray temp;
    temp.reserve(PUBLIC_PART_LEN);

    auto pIt = privateKey.cbegin();

    for (quint32 i = 0; i < PUBLIC_PART_LEN; ++i)
    {
        if (((i + 1) % 2) == 0)
        {
            temp.append(*pIt++);
        }
        else
        {
            temp.append(getRandomBoundedNumber<char>());
        }
    }

    return temp;
}

QByteArray BaseGenerateStrategy::generatePrivateKey() const
{
    QByteArray temp;
    temp.resize(PRIVATE_PART_LEN);

    std::generate(temp.begin(), temp.end(), [&]()
                  {
                      return getRandomBoundedNumber<char>();
                  });

    return temp;
}
