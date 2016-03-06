# mC -> C
# mB -> B
# m0 -> 2
# m1 -> 3

BEGIN {
    FS = ";"
    state = 1
    col[1] = "0"
    col[2] = "1"
    col[3] = "c"
    col[4] = "L"
    col[5] = "R"
    col[6] = "b"
    col[7] = "2"
    col[8] = "3"
    col[9] = "C"
    col[10] = "mL"
    col[11] = "mR"
    col[12] = "B"
}

{
    for (i = 1; i <= NF; i++) {
        if ($i != "-") {
            split($i, tuple, ",")
            print state, col[i], "P"tuple[2] "," tuple[3], tuple[1]
        }
    }
    state++
}
