#include <QCoreApplication>
#include <QFlags>
#include <QVector3D>

struct bitconv
{
    constexpr bitconv(const std::uint32_t u) : u{u} {}
    constexpr bitconv(const float f) : f{f} {}

    union {
        std::uint32_t u;
        float f;
    };
};

int main(int argc, char *argv[])
{
    enum TestResult {
        BadFloatingPointMath    = (1 << 0),
        BadQVectorNormalized    = (1 << 1),
        BadQVectorLengthSquared = (1 << 2),
        BadQVectorLength        = (1 << 3),
        BadQHypot               = (1 << 4),
        BadStdHypot             = (1 << 5),
    };

    const auto app = QCoreApplication{argc, argv};

    const auto s = bitconv{1104197782U}.f;
    const auto l = bitconv{1084453761U}.f;
    const auto x = bitconv{3206494268U}.f;
    const auto y = bitconv{1084374055U}.f;
    const auto z = bitconv{0U}.f;

    const auto nx = bitconv{3187236701U}.f;
    const auto ny = bitconv{1065228379U}.f;
    const auto nz = bitconv{0U}.f;

    auto testResults = QFlags<TestResult>{};

    if (std::sqrt(x * x + y * y + z * z) != l)
        testResults.setFlag(BadFloatingPointMath);
    if (QVector3D{x, y, z}.normalized() != QVector3D{nx, ny, nz})
        testResults.setFlag(BadQVectorNormalized);
    if (QVector3D{x, y, z}.lengthSquared() != s)
        testResults.setFlag(BadQVectorLengthSquared);
    if (QVector3D{x, y, z}.length() != l)
        testResults.setFlag(BadQVectorLength);
    if (qHypot(x, y, z) != l)
        testResults.setFlag(BadQHypot);
    if (std::hypot(x, y, z) != l)
        testResults.setFlag(BadStdHypot);

    return testResults;
}
