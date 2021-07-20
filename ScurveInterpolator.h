#ifndef SCURVEINTERPOLATOR_H
#define SCURVEINTERPOLATOR_H

#include "math.h"

constexpr double one_sixth = 1.0 / 6;

#define square(x) (x * x)
#define cubic(x) (x * x * x)
#define max(a, b) a>b?a:b

// S-Curve interpolator
class Scurve_Interpolator
{
private:
    struct profile_segment
    {
        double t0, t;
        float j, a, v, p;
    };
    profile_segment segment[7];
    float max_jer = 255000;
    float max_vel = 500;
    float max_acc = 8000;
    float vel_start = 30;
    float vel_end = 40;
    double time_tick = 0.001;

    static float profile_seg_pos(profile_segment &seg, double time)
    {
        return seg.p + seg.v * time + 0.5 * seg.a * square(time) + one_sixth * seg.j * cubic(time);
    }
    static float profile_seg_vel(profile_segment &seg, double time)
    {
        return seg.v + seg.a * time + 0.5 * seg.j * square(time);
    }
    static float profile_seg_acc(profile_segment &seg, double time)
    {
        return seg.a + seg.j * time;
    }
    static float profile_seg_jrk(profile_segment &seg, double time)
    {
        return seg.j;
    }
    // Find the seg index for an S-Curve for "time".
    static int profile_index(profile_segment *curve, double time)
    {
        int i;
        for (i = 1; i < 7; i++)
        {
            if (curve[i].t0 > time)
                break;
        }
        return i - 1;
    }
    // Get the current position, velocity, acceleration or jerk
    // for an S-Curve at the given time.
    static float profile_pos(profile_segment *curve, double time)
    {
        auto i = profile_index(curve, time);
        return profile_seg_pos(curve[i], time - curve[i].t0);
    };
    static float profile_vel(profile_segment *curve, double time)
    {
        auto i = profile_index(curve, time);
        return profile_seg_vel(curve[i], time - curve[i].t0);
    }
    static float profile_acc(profile_segment *curve, double time)
    {
        auto i = profile_index(curve, time);
        return profile_seg_acc(curve[i], time - curve[i].t0);
    }
    static float profile_jrk(profile_segment *curve, double time)
    {
        auto i = profile_index(curve, time);
        return profile_seg_jrk(curve[i], time - curve[i].t0);
    }
    // Connect the piecewise sections of an S-Curve together to
    // ensure a smooth graph.
    void calculate_profile()
    {
        auto last_curve = segment[0];
        for (int i = 1; i < 7; i++)
        {
            segment[i].t0 = last_curve.t0 + last_curve.t;
            segment[i].a = profile_seg_acc(last_curve, last_curve.t);
            segment[i].v = profile_seg_vel(last_curve, last_curve.t);
            segment[i].p = profile_seg_pos(last_curve, last_curve.t);
            last_curve = segment[i];
        }
    };
    void recalculate_profile()
    {
        double t1 = 0;
        double t2 = 0;
        double t4 = 0;
        double t5 = 0;

        segment[0] = profile_segment{0, 0, max_jer, 0, vel_start, 0};
        segment[1] = profile_segment{0, 0, 0, 0, 0, 0};
        segment[2] = profile_segment{0, 0, -max_jer, 0, 0, 0};
        segment[3] = profile_segment{0, 0, 0, 0, 0, 0};
        segment[4] = profile_segment{0, 0, -max_jer, 0, 0, 0};
        segment[5] = profile_segment{0, 0, 0, 0, 0, 0};
        segment[6] = profile_segment{0, 0, max_jer, 0, 0, 0};

        float p = 0;

        float test_vel_min = max(vel_start, vel_end);
        float test_vel_max = max_vel;
        float test_vel = test_vel_max; // Start at max vel - probably the solution
        while (test_vel_max - test_vel_min > 1)
        { // Solve to within 5 velocity units
            if (square(max_acc) / max_jer >= (test_vel - vel_start))
            {
                t1 = sqrt((test_vel - vel_start) / max_jer);
                t2 = 0;
            }
            else
            {
                t1 = max_acc / max_jer;
                t2 = (test_vel - vel_start - max_acc * t1) / max_acc;
            }

            if (square(max_acc) / max_jer >= (test_vel - vel_end))
            {
                t4 = sqrt((test_vel - vel_end) / max_jer);
                t5 = 0;
            }
            else
            {
                t4 = max_acc / max_jer;
                t5 = (test_vel - vel_end - max_acc * t4) / max_acc;
            }

            segment[0].t = segment[2].t = t1;
            segment[4].t = segment[6].t = t4;
            segment[1].t = t2;
            segment[5].t = t5;
            calculate_profile();

            p = profile_pos(segment, segment[6].t0 + segment[6].t);

            if (p > p_target)
            {
                // Need to reduce velocity
                test_vel_max = test_vel;
                test_vel = (test_vel_max + test_vel_min) / 2.0;
            }
            else
            {
                if (p > (p_target - 0.4))
                {
                    break;
                }
                else
                {
                    // Increase velocity
                    test_vel_min = test_vel;
                    test_vel = (test_vel_max + test_vel_min) / 2.0;
                }
            }
        }

        // Adjust the constant velocity section to reach the target position
        auto t = (p_target - p) / test_vel;
        segment[3].t = max(t, 0);
        calculate_profile();
    }

public:
    float v = 0, p = 0, a = 0, j = 0;
    double t = 0;
    float p_target = 0;
    double t_target = 0;

    void setTarget(float t)
    {
        p_target = t;
    }

    void setMaxJerk(float j)
    {
        max_jer = abs(j);
    }

    void setMaxAcc(float a)
    {
        max_acc = abs(a);
    }

    void setMaxVel(float v)
    {
        max_vel = abs(v);
    }

    void setVelStart(float vs)
    {
        vel_start = abs(vs);
    }

    void setVelEnd(float ve)
    {
        vel_end = abs(ve);
    }

    void setTimeTick(double t_tick)
    {
        time_tick = t_tick;
    }

    void start()
    {
        recalculate_profile();
        p = 0;
        v = 0;
        a = 0;
        j = 0;
        t = 0;
        t_target = segment[6].t0 + segment[6].t;
    }

    void stop()
    {
        p = 0;
        v = 0;
        a = 0;
        j = 0;
        t = 0;
        t_target = 0;
    }

    bool update()
    {
        t += time_tick;
        if (t > 0 && t <= (segment[6].t0 + segment[6].t))
        {
            p = profile_pos(segment, t);
        }

        if (p > p_target)
        {
            p = p_target;
            return true;
        }

        if (t < segment[6].t0 + segment[6].t)
            return false;
        p = p_target;

        return true;
    }
};
#endif // SCURVEINTERPOLATOR_H
