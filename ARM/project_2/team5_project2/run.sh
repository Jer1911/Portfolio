#!/bin/bash
set -x
rm outputs/*out*
python team5_project2.py -i tests/test9_bin.txt -o outputs/test9_out
python team5_project2.py -i tests/test10_bin.txt -o outputs/test10_out
python team5_project2.py -i tests/test11_bin.txt -o outputs/test11_out
python team5_project2.py -i tests/jertest12_bin.txt -o outputs/jertest12_out
python team5_project2.py -i tests/kamtest1.txt -o outputs/kamtest1_out
python team5_project2.py -i tests/jertest15.txt -o outputs/jertest15_out
python team5_project2.py -i tests/laktest1.txt -o outputs/laktest1_out
python team5_project2.py -i tests/laktest2.txt -o outputs/laktest2_out
python team5_project2.py -i tests/laktest3.txt -o outputs/laktest3_out
python team5_project2.py -i tests/jertestBADSTUR.txt -o outputs/jertestBADSTUR_out
python team5_project2.py -i tests/BADSTUR_with_mem.txt -o outputs/BADSTUR_with_mem_out
python team5_project2.py -i tests/goodLDUR.txt -o outputs/goodLDUR_out
python team5_project2.py -i tests/badLDUR.txt -o outputs/badLDUR_out
python team5_project2.py -i tests/branchtest_bin.txt -o outputs/branchtest_out
python team5_project2.py -i tests/negtest.txt -o outputs/negtest_out
python team5_project2.py -i tests/finaltest3_bin.txt -o outputs/finaltest3_out
set +x

