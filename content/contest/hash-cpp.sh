# Hashes a file, ignoring all whitespace, comments and defines. Use for
# verifying that code was correctly typed.
# First do: chmod +x ./hash-cpp.sh
# ./hash-cpp.sh *.cpp start end
sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum |cut -c-6
