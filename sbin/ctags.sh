#!/bin/sh

TEST_HOME="/home/speedmax/code/apue/test_program"
LOG_DIR="$TEST_HOME/log"
LOG="ctags.log"

cd $TEST_HOME
ctags -f $TEST_HOME/test_tags -R>>$LOG_DIR/$LOG 2>$LOG_DIR/$LOG
