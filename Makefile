LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds KACTL (KTH Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build KACTL, quickly (only runs LaTeX once)"
	@echo "	make ufrj		- to build KACTL"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove ufrj.pdf"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

fast: | build
	$(LATEXCMD) content/ufrj.tex </dev/null
	$(LATEXCMD) content/ufrj-wf.tex </dev/null
	cp build/ufrj.pdf ufrj.pdf
	cp build/ufrj-wf.pdf ufrj-wf.pdf

ufrj: test-session.pdf | build
	$(LATEXCMD) content/ufrj.tex && $(LATEXCMD) content/ufrj.tex
	cp build/ufrj.pdf ufrj.pdf
	$(LATEXCMD) content/ufrj-wf.tex && $(LATEXCMD) content/ufrj-wf.tex
	cp build/ufrj-wf.pdf ufrj-wf.pdf

clean:
	cd build && rm -f ufrj.aux ufrj.log ufrj.tmp ufrj.toc ufrj.pdf ufrj.ptc

veryclean: clean
	rm -f ufrj.pdf test-session.pdf

.PHONY: help fast ufrj clean veryclean

build:
	mkdir -p build/

test:
	./doc/scripts/run-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K%.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
