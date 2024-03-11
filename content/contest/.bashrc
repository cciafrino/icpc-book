b()(g++ -DLOC -O2 -std=c++20 -Wall -W -Wfatal-errors \
		 -Wconversion -Wshadow -Wlogical-op \
		 -Wfloat-equal -o $1 $1.cpp )
d()(b $@ -O0 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined)
run()( $@ && echo start >&2 && time ./$2)
hash-cpp()(sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P \
	-fpreprocessed | tr -d '[:space:]' | md5sum |cut -c-6)
# Other compilation flags:
# -Wformat=2 -Wshift-overflow=2 -Wcast-qual
# -Wcast-align -Wduplicated-cond
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
# -fno-sanitize-recover -fstack-protector
# Print optimization info: -fopt-info-all