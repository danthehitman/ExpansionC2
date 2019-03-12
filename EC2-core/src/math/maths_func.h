#pragma once

#include<math.h>

namespace ec2 {
    namespace maths {

        inline float toRadians(float degrees)
        {
            return degrees * (M_PI / 180.0f);
        }
    }
}
