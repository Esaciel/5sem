all : ready/report.pdf ready/stud-unit-test-report.json

ready:
	mkdir -p ready

unity:
	mkdir -p unit/obj

INCPATH := -I. -I. -Icode/src/Defs -Icode/src/Errors -Icode/src/IO -Icode/src/Solution -Icode/src/Extras
CXXFLAGS := -std=c++20 -g -O0 -Wall -fprofile-arcs -ftest-coverage --coverage
LDFLAGS := -lgtest -lgtest_main -lpthread -lgcov --coverage

ready/report.pdf : ready
	cp report/report.pdf ready/report.pdf

report/report.pdf: report/report.tex report/lib.bib
	cd report && pdflatex.exe report.tex
	cd report && bibtex.exe report.aux
	cd report && pdflatex.exe report.tex
	cd report && pdflatex.exe report.tex

ready/stud-unit-test-report.json: unit_res

unit_res : ready unit
	apt install libxml2-utils -y -qq
	@unit/unit.exe --gtest_output=xml:unit/obj/cvg.xml
	@mkdir -p unit/gcovs
	@TIMESTAMP=$$(date +"%Y-%m-%dT%H:%M:%S%:z") ; \
	cp unit/obj/*.gcda . && cp unit/obj/*.gcno . ; \
	COVERAGE=$$(gcov -o . code/src/Solution/solution.cpp 2>/dev/null | \
		grep "Lines executed:" | \
		tail -1 | \
		sed 's/Lines executed://;s/%.*//' | tr -d ' ') ; \
	rm *.gcda *.gcno ; \
	mv *.gcov unit/gcovs ; \
	PASSED=$$(xmllint --xpath 'string(//testsuites/@tests)' unit/obj/cvg.xml) ; \
	FAILED=$$(xmllint --xpath 'string(//testsuites/@failures)' unit/obj/cvg.xml) ; \
	TOTAL=$$(($$PASSED + $$FAILED)) ; \
	if [ -z "$$COVERAGE" ]; then COVERAGE=0; fi ; \
	echo '{ "timestamp": "'$$TIMESTAMP'", "total": '$$TOTAL', "passed": '$$PASSED', "failed": '$$FAILED', "coverage": '$$COVERAGE'}' > stud-unit-test-report.json
	mv stud-unit-test-report.json ready



unit: unity unit/obj/solution.o unit/obj/extras.o unit/obj/unit.o
	g++ $(LFLAGS) -o unit/unit.exe unit/obj/solution.o unit/obj/extras.o unit/obj/unit.o $(LDFLAGS)

unit/obj/solution.o: code/src/Solution/solution.cpp code/src/Solution/solution.hpp \
		code/src/Defs/definitions.hpp \
		code/src/Errors/err.hpp \
		code/src/Extras/extras.hpp
	g++ -c $(CXXFLAGS) $(INCPATH) -o unit/obj/solution.o code/src/Solution/solution.cpp

unit/obj/extras.o: code/src/Extras/extras.cpp code/src/Extras/extras.hpp \
		code/src/Defs/definitions.hpp
	g++ -c $(CXXFLAGS) $(INCPATH) -o unit/obj/extras.o code/src/Extras/extras.cpp

unit/obj/unit.o: ready code/src/Solution/solution.hpp unit/unit.cpp
	g++ -c $(CXXFLAGS) $(INCPATH) -o unit/obj/unit.o unit/unit.cpp

.PHONY : clean fullclean clean_report
clean :
	rm -f unit/obj/* ready/* unit/*.exe *.gcov unit/gcovs/* ready/*
fullclean : clean
	rm -f report/*.aux report/*.bbl report/*.blg report/*.out report/*.toc report/*.log report/*.gz
	rm -rf ready
clean_report :
	rm -f report/report.pdf
