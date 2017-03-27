def inv(c):
    """
    Invert an encoding number
    0,L <-> 1,L : 0 <-> 4
    1,R <-> 0,R : 1 <-> 3

    2,L <-> 2,L : 2 <-> 2
    2,R <-> 2,R : 5 <-> 5
    """
    if c in ('2', '5'):
        return c
    return str(4 - int(c))


def dual(encoding):
    """Take an encoding of a TM and return it's dual TM

    The dual of a TM is where all the 0s are treated as 1s and vice versa"""
    tm = list(encoding)
    tm[0], tm[2] = tm[2], tm[0]
    tm[6], tm[8] = tm[8], tm[6]
    tm[1], tm[3] = inv(tm[3]), inv(tm[1])
    tm[7], tm[9] = inv(tm[9]), inv(tm[7])
    tm[5], tm[11] = inv(tm[5]), inv(tm[11])

    # special case, don't convert a 21 to 23
    for i in range(0, 11, 2):
        if tm[i] == '2':
            tm[i+1] = '1'
            break

    return "".join(tm)


def remove_duals(input_file, output_file):
    encoding = "000111211015"
    print(dual(encoding))


if __name__ == "__main__":
    print("Finding a removing dual (nb) TMs")
    input_file, output_file = "../data/all_nb_TMs.txt", "../data/dualless_nb_TMs.txt"
    remove_duals(input_file, output_file)
    print("DONE")

    print("Finding a removing dual (b) TMs")
    input_file, output_file = "../data/all_b_TMs.txt", "../data/dualless_b_TMs.txt"
    remove_duals(input_file, output_file)
    print("DONE")