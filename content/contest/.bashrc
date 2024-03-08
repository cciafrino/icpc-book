b()(g++ -DLOC -O2 -std=c++20 -Wall -W -Wfatal-errors \
		 -Wconversion -Wshadow -Wlogical-op \
		 -Wfloat-equal -o $1 $1.cpp )
d()(b $@ -O0 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined)
run()( $@ && echo start >&2 && time ./$2.e )
# Other compilation flags:
# -Wformat=2 -Wshift-overflow=2 -Wcast-qual
# -Wcast-align -Wduplicated-cond
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
# -fno-sanitize-recover -fstack-protector
# Print optimization info: -fopt-info-all