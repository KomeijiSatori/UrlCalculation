"""
This python file is used to generate url files
"""

import random
import string

with open("input/input.txt", "w") as fp:
    letters = string.ascii_lowercase + string.digits
    for i in range(int(1e8)):
        segment_cnt = 2
        s = "https://"
        for j in range(segment_cnt):
            segment_len = 2
            s += ''.join(random.choice(letters) for i in range(segment_len)) + "/"
        fp.write(s + "\n")
