all : ready/app-cli-release ready/app-cli-debug ready/app-tui-release ready/app-tui-debug ready/stud-unit-test-report.json ready/report.pdf

ready :
	mkdir -p ready

meson_install :
	dpkg -l | grep -qw meson || apt install meson -y -qq
	dpkg -l | grep -qw ninja-build || apt install ninja-build -y -qq

build_apps : meson_install
	mv code/apps/meson.txt code/apps/meson.build 2>/dev/null || echo "" > /dev/null
	cd code/apps && meson setup outdir
	ninja -C code/apps/outdir

ready/app-cli-release : ready build_apps
	cp code/apps/outdir/app-cli-release ready/.

ready/app-cli-debug : ready build_apps
	cp code/apps/outdir/app-cli-debug ready/.

ready/app-tui-release : ready build_apps
	cp code/apps/outdir/app-tui-release ready/.

ready/app-tui-debug : ready  build_apps
	cp code/apps/outdir/app-tui-debug ready/.

apps : ready build_apps
	cp code/apps/outdir/app-cli-release ready/.
	cp code/apps/outdir/app-cli-debug ready/.
	cp code/apps/outdir/app-tui-release ready/.
	cp code/apps/outdir/app-tui-debug ready/.

build_unit : meson_install
	mv code/unit/meson.txt code/unit/meson.build  2>/dev/null || echo "" > /dev/null
	cd code/unit && meson setup outdir
	ninja -C code/unit/outdir

test_unit : build_unit
	cd code/unit/outdir && ./unit_tests --gtest_output=xml:cvg.xml

ready/stud-unit-test-report.json : ready test_unit
	dpkg -l | grep -qw libxml2-utils || apt install libxml2-utils -y -qq
	@TIMESTAMP=$$(date +"%Y-%m-%dT%H:%M:%S%:z") ; \
	COVERAGE=$$(cd code/unit/outdir && find . -type f -name "*.gcda" -not \( -name ".._src_unit.cpp.gcda" -o -name ".._src_Measurements_measurements.cpp.gcda" \) -exec gcov {} \; | \
		grep "Lines executed:" | \
		tail -1 | \
		sed 's/Lines executed://;s/%.*//' | tr -d ' ') ; \
	PASSED=$$(xmllint --xpath 'string(//testsuites/@tests)' code/unit/outdir/cvg.xml) ; \
	FAILED=$$(xmllint --xpath 'string(//testsuites/@failures)' code/unit/outdir/cvg.xml) ; \
	TOTAL=$$(($$PASSED + $$FAILED)) ; \
	if [ -z "$$COVERAGE" ]; then COVERAGE=0; fi ; \
	echo '{ "timestamp": "'$$TIMESTAMP'", "total": '$$TOTAL', "passed": '$$PASSED', "failed": '$$FAILED', "coverage": '$$COVERAGE'}' > stud-unit-test-report.json
	mv stud-unit-test-report.json ready
	rm code/unit/outdir/cvg.xml
	rm code/unit/outdir/*.gcov

ready/report.pdf : ready report/report.pdf
	cp report/report.pdf ready/report.pdf

report/report.pdf: report/report.tex report/lib.bib
	cd report && pdflatex report.tex
	cd report && bibtex report.aux
	cd report && pdflatex report.tex
	cd report && pdflatex report.tex
	ls stuff/pdfcleaner.txt > /dev/null 2>/dev/null && stuff/pdfcleaner.txt report/report.pdf || echo "" > /dev/null

.PHONY : clean format pdfcompress force

clean :
	rm -f  ready/* report/*.aux report/*.bbl report/*.blg report/*.out report/*.toc report/*.log report/*.gz
	rm -rf ready
	rm -rf code/apps/outdir
	rm -rf code/unit/outdir
	mv code/unit/meson.build code/unit/meson.txt 2>/dev/null || echo ""
	mv code/apps/meson.build code/apps/meson.txt 2>/dev/null || echo ""

format :
	find . -name "*.cpp" -exec clang-format -style=LLVM -i {} \;
	find . -name "*.hpp" -exec clang-format -style=LLVM -i {} \;

pdfcompress :
	which cleanpdf && find . -name "*.pdf" -exec cleanpdf {} \;

force :
