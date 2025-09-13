import math
import matplotlib.pyplot as plt
import time


class profile_segment:
    def __init__(self, t0, t, j, a, v, p):
        self.t0 = t0
        self.t = t
        self.j = j
        self.a = a
        self.v = v
        self.p = p


class Scurve_Interpolator:
    def __init__(self):
        self.segment = []
        self.max_jer = 255000
        self.max_vel = 500
        self.max_acc = 8000
        self.vel_start = 30
        self.vel_end = 10
        self.time_tick = 0.001

        self.p_target = 0
        self.t_target = 0
        self.v = 0
        self.p = 0
        self.a = 0
        self.j = 0
        self.t = 0

        for i in range(0, 7):
            self.segment.append(profile_segment(0, 0, 0, 0, 0, 0))

    def profile_seg_pos(self, seg, time=0.0):
        return seg.p + seg.v * time + 0.5 * seg.a * time * time + seg.j * time * time * time * (1 / 6)

    def profile_seg_vel(self, seg, time=0.0):
        return seg.v + seg.a * time + 0.5 * seg.j * time * time

    def profile_seg_acc(self, seg, time=0.0):
        return seg.a + seg.j * time

    def profile_seg_jrk(self, seg, time=0.0):
        return seg.j

    # Find the seg index for an S-Curve for "time".
    def profile_index(self, curve, time=0.0):
        index = 0
        for index in range(1, 8):
            if index == 7:
                break
            if curve[index].t0 > time:
                break
        return index - 1

    # Get the current position, velocity, acceleration or jerk
	# for an S-Curve at the given time.
    def profile_pos(self, curve, time=0.0):
        i = self.profile_index(curve, time)
        return self.profile_seg_pos(curve[i], time - curve[i].t0)

    def profile_vel(self, curve, time=0.0):
        i = self.profile_index(curve, time)
        return self.profile_seg_vel(curve[i], time - curve[i].t0)

    def profile_acc(self, curve, time=0.0):
        i = self.profile_index(curve, time)
        return self.profile_seg_acc(curve[i], time - curve[i].t0)

    def profile_jrk(self, curve, time=0.0):
        i = self.profile_index(curve, time)
        return self.profile_seg_jrk(curve[i], time - curve[i].t0)

    # Connect the piecewise sections of an S-Curve together to
	# ensure a smooth graph.

    def calculate_profile(self):
        last_curve = self.segment[0]
        for i in range(1, 7):
            self.segment[i].t0 = last_curve.t0 + last_curve.t
            self.segment[i].a = self.profile_seg_acc(last_curve, last_curve.t)
            self.segment[i].v = self.profile_seg_vel(last_curve, last_curve.t)
            self.segment[i].p = self.profile_seg_pos(last_curve, last_curve.t)
            last_curve = self.segment[i]

    def recalculate_profile(self):
        t1 = 0.0
        t2 = 0.0
        t4 = 0.0
        t5 = 0.0

        self.segment[0] = profile_segment(
            0, 0, self.max_jer, 0, self.vel_start, 0)
        self.segment[1] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[2] = profile_segment(0, 0, -self.max_jer, 0, 0, 0)
        self.segment[3] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[4] = profile_segment(0, 0, -self.max_jer, 0, 0, 0)
        self.segment[5] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[6] = profile_segment(0, 0, self.max_jer, 0, 0, 0)

        p = 0
        test_vel_min = max(self.vel_start, self.vel_end)
        test_vel_max = self.max_vel
        test_vel = test_vel_max
        while test_vel_max - test_vel_min > 1:
            if (self.max_acc * self.max_acc) / self.max_jer >= test_vel - self.vel_start:
                t1 = math.sqrt((test_vel - self.vel_start) / self.max_jer)
                t2 = 0
            else:
                t1 = self.max_acc / self.max_jer
                t2 = (test_vel - self.vel_start -
                      self.max_acc * t1) / self.max_acc

            if (self.max_acc * self.max_acc) / self.max_jer >= test_vel - self.vel_end:
                t4 = math.sqrt((test_vel - self.vel_end) / self.max_jer)
                t5 = 0
            else:
                t4 = self.max_acc / self.max_jer
                t5 = (test_vel - self.vel_end -
                      self.max_acc * t4) / self.max_acc

            self.segment[0].t = t1
            self.segment[2].t = t1
            self.segment[4].t = t4
            self.segment[6].t = t4
            self.segment[1].t = t2
            self.segment[5].t = t5

            self.calculate_profile()

            p = self.profile_pos(
                self.segment, self.segment[6].t0 + self.segment[6].t)

            if p > self.p_target:
                # Need to reduce velocity
                test_vel_max = test_vel
                test_vel = (test_vel_max + test_vel_min) / 2.0
            else:
                if p > self.p_target - 0.1:
                    break
                else:
                    # Increase velocity
                    test_vel_min = test_vel
                    test_vel = (test_vel_max + test_vel_min) / 2.0

        # Adjust the constant velocity section to reach the target position
        t = (self.p_target - p) / test_vel
        self.segment[3].t = max(t, 0)
        self.calculate_profile()

    def recalculate_profile_from_t(self):
        t1 = 0.0
        t2 = 0.0
        t4 = 0.0
        t5 = 0.0

        self.segment[0] = profile_segment(
            0, 0, self.max_jer, 0, self.vel_start, 0)
        self.segment[1] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[2] = profile_segment(0, 0, -self.max_jer, 0, 0, 0)
        self.segment[3] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[4] = profile_segment(0, 0, -self.max_jer, 0, 0, 0)
        self.segment[5] = profile_segment(0, 0, 0, 0, 0, 0)
        self.segment[6] = profile_segment(0, 0, self.max_jer, 0, 0, 0)

        p = 0
        _t_total = 0
        test_vel_min = max(self.vel_start, self.vel_end)
        test_vel_max = self.max_vel
        test_vel = test_vel_max

        while test_vel_max - test_vel_min > 1:
            if (self.max_acc * self.max_acc) / self.max_jer >= test_vel - self.vel_start:
                t1 = math.sqrt((test_vel - self.vel_start) / self.max_jer)
                t2 = 0
            else:
                t1 = self.max_acc / self.max_jer
                t2 = (test_vel - self.vel_start -
                      self.max_acc * t1) / self.max_acc

            if (self.max_acc * self.max_acc) / self.max_jer >= test_vel - self.vel_end:
                t4 = math.sqrt((test_vel - self.vel_end) / self.max_jer)
                t5 = 0
            else:
                t4 = self.max_acc / self.max_jer
                t5 = (test_vel - self.vel_end -
                      self.max_acc * t4) / self.max_acc

            _t_total = t1*2 + t4*2 + t2 + t5

            if _t_total > self.t_target:
                # Need to reduce velocity
                test_vel_max = test_vel
                test_vel = (test_vel_max + test_vel_min) / 2.0
            else:
                if _t_total > self.t_target - 0.0005:
                    break
                else:
                    # Increase velocity
                    test_vel_min = test_vel
                    test_vel = (test_vel_max + test_vel_min) / 2.0

        # Adjust the constant velocity section to reach the target position
        t = self.t_target - _t_total
        self.segment[3].t = max(t, 0)
        self.segment[0].t = t1
        self.segment[2].t = t1
        self.segment[4].t = t4
        self.segment[6].t = t4
        self.segment[1].t = t2
        self.segment[5].t = t5
        self.calculate_profile()

    def start(self):
        if self.p_target != 0:
            self.recalculate_profile()
            self.t_target = self.segment[6].t0 + self.segment[6].t
        else:
            self.recalculate_profile_from_t()
            self.p_target = self.profile_pos(
                self.segment, self.segment[6].t0 + self.segment[6].t)
        self.p = 0
        self.v = 0
        self.a = 0
        self.j = 0
        self.t = 0
    
    def stop(self):
        self.p = 0
        self.v = 0
        self.a = 0
        self.j = 0
        self.t = 0
        self.t_target = 0

    def update(self):
        self.t += self.time_tick

        if self.t > 0 and self.t <= self.segment[6].t0 + self.segment[6].t:
            self.v = self.profile_vel(self.segment, self.t)
            self.p = self.profile_pos(self.segment, self.t)
            self.a = self.profile_acc(self.segment, self.t)
            self.j = self.profile_jrk(self.segment, self.t)

        if self.p > self.p_target:
            self.p = self.p_target
            return True

        if self.t < self.segment[6].t0 + self.segment[6].t:
            return False

        self.v = self.profile_seg_vel(self.segment[6], self.segment[6].t)
        self.p = self.profile_seg_pos(self.segment[6], self.segment[6].t)
        self.a = self.profile_seg_acc(self.segment[6], self.segment[6].t)
        self.j = self.profile_seg_jrk(self.segment[6], self.segment[6].t)

        return True

    def set_moving_parameter(self, **parameter):
        for key, value in parameter.items():
            if key == 'a':
                self.max_acc = abs(value)
            if key == 'j':
                self.max_jer = abs(value)
            if key == 'v':
                self.max_vel = abs(value)
            if key == 'vs':
                self.vel_start = abs(value)
            if key == 've':
                self.vel_end = abs(value)

    def set_moving_distance(self, distance):
        self.p_target = abs(distance)
        self.t_target = 0

    def set_moving_time(self, _time):
        self.t_target = abs(_time)
        self.p_target = 0

    def find_short_point(self, x0, y0, x1, y1, F, v, angle):
        if x0 == x1 and y0 == y1:
            return x0, y0

        xv = v * math.cos(math.radians(angle))
        yv = v * math.sin(math.radians(angle))

        K1 = -yv * x1 + xv * y1 
        K2 = K1 - y0 * xv
        K3 = K1 - y1 * xv

        a = v ** 2 * xv ** 2 + v ** 2 * yv ** 2 - xv ** 2 * F ** 2 - F ** 2 * yv ** 2
        b = -2 * x0 * v ** 2 * xv ** 2 + v ** 2 * 2 * yv * K2 + 2 * x1 * xv ** 2 * F ** 2 - F ** 2 * 2 * yv * K3
        c = v ** 2 * xv ** 2 * x0 ** 2 + v ** 2 * K2 ** 2 - xv ** 2 * F ** 2 * x1 ** 2 - F ** 2 * K3 ** 2

        d = (b**2) - (4*a*c)

        # find two solutions
        sol1 = (-b - math.sqrt(d))/(2*a)
        sol2 = (-b + math.sqrt(d))/(2*a)
        
        x = sol1

        if math.cos(math.radians(angle)) > 0:
            if sol2 - x1 > 0:
                x = sol2
        else:
            if sol2 - x1 < 0:
                x = sol2

        k = math.tan(math.radians(angle))
        y = k * x + (y1 - k * x1)

        return x, y
        

    def find_sync_point(self, x1, y1, z1, x2, y2, z2, vel, angle, time_offset=0):
        start_time = time.time()
        rad = math.radians(angle)

        Cmx, Cmy = self.find_short_point(x1, y1, x2, y2, self.max_vel, vel, angle)
        # print('Cmx:{0}, Cmy:{1}'.format(Cmx, Cmy))
        BCm = math.sqrt(math.pow(Cmx - x2, 2) + math.pow(Cmy - y2, 2))

        step = 1
        i = 1

        Cx = Cmx
        Cy = Cmy

        # A
        # - -
        # B ---- Cm - C - D
        # B ---- Cm ----- D - C

        total_time = time.time() - start_time

        while i < 200:
            
            BC = BCm + step * i
            # print('BC:' + str(BC))

            i = i + 1

            Cx = BC * math.cos(rad) + x2
            Cy = BC * math.sin(rad) + y2

            # print('Cx:{0}, Cy:{1}'.format(Cx, Cy))

            AC = math.sqrt(math.pow(Cx - x1, 2) + math.pow(Cy - y1, 2))
            # print('AC:' + str(AC))
            ACz = math.sqrt(math.pow(AC, 2) + math.pow(z2 - z1, 2))
            # print('ACz: ' + str(ACz))
            self.p_target = ACz
            self.start()
            t = self.t_target
            # print('robot time: ' + str(t))
            td = time.time() - start_time
            total_time = t + td + time_offset
            # print('total time: ' + str(total_time))
            BD = total_time * vel

            # print('BD: ' + str(BD))
            
            if BC - BD > 0.5:
                break

        # print('total time: ' + str(total_time))

        return Cx, Cy

moving = Scurve_Interpolator()
moving.max_vel = 2000
moving.max_acc = 10000
moving.vel_start = 50
moving.vel_end = 50
moving.max_jer = 500000

a = time.time()
print(moving.find_sync_point(-100, 100, -200, -50, 100, -10, 100, 0))
print(time.time() - a)

# a = time.time()
# print(moving.find_sync_point(-100, 100, 20, -50, 100, -10))
# print(time.time() - a)