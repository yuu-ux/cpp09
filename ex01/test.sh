# 42
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# 42
./RPN "7 7 * 7 -"
# 0
./RPN "1 2 * 2 / 2 * 2 4 - +"
# minus
./RPN "1 2 -"
# Error
./RPN "(1 + 1)"
# zero by division
./RPN "8 0 /"
# overflow (up)
./RPN "8 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * *"
# overflow (under)
./RPN "0 9 - 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
