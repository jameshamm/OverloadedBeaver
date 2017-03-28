def is_interesting(x):
    """
    Some hand made patterns for TMs that will loop forever on blank input
    """

    # XX XX 1[1, 3, 5] XX XX 1[1, 3, 5] will move right on blanks and nothing else
    if x[4] == '1' and x[5] in ('1', '3', '5') and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False

    # 02 XX 00 XX XX XX will replace 0 with blank and vice versa forever
    if x[0] == '0' and x[1] == '2' and x[4] == '0' and x[5] == '0':
        return False
    # The dual of the above TM class
    if x[2] == '0' and x[3] == '2' and x[4] == '0' and x[5] == '4':
        return False

    # Never writes any symbol except blank
    if x[4] == '1' and x[5] in ('2', '5') and x[10] == '0' and x[11] in ('2', '5'):
        return False

    # Blank goes to 0, and 0 goes to blank, swapping states
    if x[4] == '1' and x[5] == '0' and x[6] == '0' and x[7] == '2':
        return False
    # Dual of above
    if x[4] == '1' and x[5] == '4' and x[8] == '0' and x[9] == '2':
        return False

    # Loops between states switching blank and 0
    if x[0] == '1' and x[1] == '2' and x[4] == '0' and x[5] == '0' and x[10] == '0' and x[11] in ('0', '2'):
        return False
    # Dual of above
    if x[2] == '1' and x[3] == '2' and x[4] == '0' and x[5] == '4' and x[10] == '0' and x[11] in ('2', '4'):
        return False

    if x[4] == '1' and x[5] in ('1', '3', '5') and x[10] == '0' and x[11] in ('1', '3', '5'):
        return False

    if x[4] == '1' and x[5] == '2' and x[10] == '1' and x[11] == '2':
        return False

    if x[4] == '1' and x[5] == '2' and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False

    if x[4] == '1' and x[5] == '0' and x[6] == '1' and x[7] == '0':
        return False
    if x[4] == '1' and x[5] == '4' and x[8] == '1' and x[7] == '4':
        return False

    # Missed this at first! Moves right on blank
    if x[4] == '0' and x[5] in ('1', '3', '5'):
        return False

    if x[4] == '1' and x[5] == '0' and x[6] == '1' and x[7] in ('1', '3', '5') and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False
    if x[4] == '1' and x[5] == '4' and x[8] == '1' and x[9] in ('1', '3', '5') and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False

    if x[0] == '1' and x[1] == '2' and x[4] == '0' and x[5] == '0' and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False
    if x[2] == '1' and x[3] == '2' and x[4] == '0' and x[5] == '4' and x[10] == '1' and x[11] in ('1', '3', '5'):
        return False

    # If it never writes a 0, and needs a 0 to halt, it must loop
    if x[6] == '2' and x[2] in ('0', '1') and x[3] in ('1', '2', '4', '5') and x[4] in ('0', '1') and x[5] in ('1', '2', '4', '5') and x[8] in ('0', '1') and x[9] in ('1', '2', '4', '5') and x[10] in ('0', '1') and x[11] in ('1', '2', '4', '5'):
        return False
    # Dual, needs a 1 to halt
    if x[8] == '2' and x[0] in ('0', '1') and x[1] in ('0', '2', '3', '5') and x[4] in ('0', '1') and x[5] in ('0', '2', '3', '5') and x[6] in ('0', '1') and x[7] in ('0', '2', '3', '5') and x[10] in ('0', '1') and x[11] in ('0', '2', '3', '5'):
        return False

    if x[4] == '1' and x[5] == '3' and x[6] == '1' and x[7] == '3' and x[10] == '1' and x[11] == '0':
        return False
    if x[4] == '1' and x[5] == '1' and x[8] == '1' and x[9] == '1' and x[10] == '1' and x[11] == '4':
        return False

    return True


def remove_bad(input_file, output_file):
    with open(input_file, "r") as f:
        lines = f.readlines()
    
    lines = [line.strip() for line in lines]
    seen = set()

    lines = [line for line in lines if is_interesting(line)]

    lines = sorted(lines)

    with open(output_file, "w+") as f:
        f.write("\n".join(lines))


if __name__ == "__main__":
    print("Finding some bad (b) TMs")
    input_file, output_file = "../data/dualless_b_TMs.txt", "../data/trimmed_b_TMs.txt"
    remove_bad(input_file, output_file)
    print("DONE")