#ifndef SCURVEINTERPOLATOR_H
#define SCURVEINTERPOLATOR_H

#include "math.h"
#include <iostream>
#include <chrono>

constexpr double one_sixth = 1.0 / 6;

#define square(x) (x * x)
#define cubic(x) (x * x * x)
#define max(a, b) a>b?a:b

#define M_PI 3.14159265358979323846

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

    std::pair<double, double> find_short_point(double x0, double y0, double x1, double y1, double F, double v, double angle) {
        if (x0 == x1 && y0 == y1)
        {
            return std::make_pair(x0, y0);
        }

        double xv = v * cos(angle * M_PI / 180.0);
        double yv = v * sin(angle * M_PI / 180.0);

        double K1 = -yv * x1 + xv * y1;
        double K2 = K1 - y0 * xv;
        double K3 = K1 - y1 * xv;

        double a = v * v * xv * xv + v * v * yv * yv - xv * xv * F * F - F * F * yv * yv;
        double b = -2 * x0 * v * v * xv * xv + v * v * 2 * yv * K2 + 2 * x1 * xv * xv * F * F - F * F * 2 * yv * K3;
        double c = v * v * xv * xv * x0 * x0 + v * v * K2 * K2 - xv * xv * F * F * x1 * x1 - F * F * K3 * K3;

        double d = (b * b) - (4 * a * c);

        // find two solutions
        double sol1 = (-b - sqrt(d)) / (2 * a);
        double sol2 = (-b + sqrt(d)) / (2 * a);
        double x = sol1;

        if (cos(angle * M_PI / 180.0) > 0) {
            if (sol2 - x1 > 0) {
                x = sol2;
            }
        }
        else {
            if (sol2 - x1 < 0) {
                x = sol2;
            }
        }

        double k = tan(angle * M_PI / 180.0);
        double y = k * x + (y1 - k * x1);

        return std::make_pair(x, y);
    }

    std::pair<double, double> find_sync_point(double x1, double y1, double z1, double x2, double y2, double z2, double vel, double angle, double time_offset=0) {
        auto start_time = std::chrono::high_resolution_clock::now();
        double rad = M_PI / 180.0 * angle;

        std::pair<double, double> short_point = find_short_point(x1, y1, x2, y2, max_vel, vel, angle);
        double Cmx = short_point.first;
        double Cmy = short_point.second;
        double BCm = sqrt(pow(Cmx - x2, 2) + pow(Cmy - y2, 2));

        int step = 1;
        int i = 1;

        double Cx = Cmx;
        double Cy = Cmy;

        double total_time;

        while (i < 200) {
            double BC = BCm + step * i;
            i++;

            Cx = BC * cos(rad) + x2;
            Cy = BC * sin(rad) + y2;

            double AC = sqrt(pow(Cx - x1, 2) + pow(Cy - y1, 2));
            double ACz = sqrt(pow(AC, 2) + pow(z2 - z1, 2));
            p_target = ACz;
            start();
            double t = t_target;
            double td = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1e6;
            total_time = t + td + time_offset;
            double BD = total_time * vel;

            if (BC - BD > 0.5) {
                break;
            }
        }

        return {Cx, Cy};
    }
};
#endif // SCURVEINTERPOLATOR_H
