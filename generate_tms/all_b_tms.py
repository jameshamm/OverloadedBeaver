from gen_tms import generate_tms


def is_interesting(x):
    """Take a string, tell some of them they are idiots

    Return True if on blank input the TM will
    loop, never halt or stop immediately"""
    # We known what the first cell reads, so we can reason about
    # the first couple of steps
    if x[4] == "2":
        # halts immediately
        return False
    if x[4:6] in ("02", "05"):
        # only writes blank to the tape
        return False
    if x[5] == "0":
        # writes a 0, moves left so stays on
        if x[4] == "0" and x[0:2] == "00":
            # same state, writes 0 and moves left
            return False
        if x[4] == "1" and x[6:8] == "10":
            # other state, writes 0 and moves left
            return False
    elif x[5] == "1":
        if x[4] == "0" and x[2:4] == "01":
            return False
        if x[4] == "1" and x[8:10] == "11":
            return False

    if "0" == x[0] == x[2] == x[4] or "1" == x[6] == x[8] == x[10]:
        return False
    return True



if __name__ == "__main__":
    print("Generating blank input TMs")
    generate_tms("../data/all_b_TMs.txt", is_interesting)
    print("DONE")