width = 300
height = 300
env_attack_time = 10
env_hold1_level = 15
env_inter1_time = 7
env_hold2_level = 10
env_inter2_time = 3
env_hold3_level = 5
env_decay_time = 10
env_sustain_level = 3
env_release = 12


max_time_width = width / 5
eg_height = height / 15
x_atk = 0
y_atk = eg_height * 0

x_l1 = env_attack_time / 10 * max_time_width
y_l1 = eg_height * env_hold1_level

x_l2 = x_l1 + (env_inter1_time / 10 * max_time_width)
y_l2 = eg_height * env_hold2_level

x_l3 = x_l2 + (env_inter2_time / 10 * max_time_width)
y_l3 = (eg_height / 10 * env_hold3_level)

x_sus = x_l3 + (env_decay_time / 10 * max_time_width)
y_sus = eg_height * env_sustain_level

x_release = x_l3 + (env_release / 10 * max_time_width)
y_release = 0.0

f = open("eg.txt", "w")

f.write(str(x_atk)+", "+str(y_atk)+"\n")
f.write(str(x_l1)+", "+str(y_l1)+ "\n")
f.write(str(x_l2)+", "+str(y_l2)+ "\n")
f.write(str(x_l3)+", "+str(y_l3)+ "\n")
f.write(str(x_sus)+", "+str(y_sus)+ "\n")
f.write(str(x_release)+", "+str(y_release)+"\n")
f.close()
