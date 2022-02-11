// Google Test
#include "gtest/gtest.h"

// Library Headers
#include <iostream>

// src/ File Headers
#include "../src/base.h"
#include "../src/and.h"
#include "../src/or.h"
#include "../src/semi_colon.h"
#include "../src/command.h"
#include "../src/connect.h"
#include "../src/rshell.h"
#include "../src/connectingStrings.h"
#include "../src/redirect.h"
#include "../src/redirectin.h"
#include "../src/redirectout.h"
#include "../src/redirectdoubleout.h"
#include "../src/piping.h"

#include <string>

using namespace std;

TEST(ParsingTest,lscommand) {
   rShell runit;
   string commandline = "ls || ls";
   runit.parsing(commandline);
}
TEST(BasicTest,Basiccommand) {
  rShell runit;
  string commandline = "echo hello world";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("hello world\n$ " ,commandOut);
}

TEST(AndTest,Andcommand) {
  rShell runit;
  string commandline = "echo A && echo B";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("A\nB\n$ " ,commandOut);
}

TEST(OrTest,Orcommand) {
  rShell runit;
  string commandline = "echo A || echo B";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("A\n$ " ,commandOut);
}

TEST(Semi_colonTest,Semic_coloncommand) {
  rShell runit;
  string commandline = "echo A ; echo B";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("A\nB\n$ " ,commandOut);
}

TEST(PrecedenceTest,Precdencecommand) {
  rShell runit;
  string commandline = "(echo A && echo B) || (echo C && echo D)";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("A\nB\n$ " ,commandOut);

}

TEST(CommandTest,CommandTestcommand) {
  rShell runit;
  string commandline = "test -d src/main.cpp && echo path exits";
  string command = "ls; ls -a";
  ::testing::internal::CaptureStdout();
  cout.flush();
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("$ (False)\n" ,commandOut);
}

TEST(GivenTest,GivenTestCommand) {
  rShell runit;
  string commandline = "cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2:wasn't found in this command\n$ error in the Rshell :in the otsexistingInputFileits not there\n",commandOut);

}

TEST(Input_RedirectTest,Input_RedirectCommand) {
  rShell runit;
  string commandline = "echo wolf < real.txt";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell echo wolf < real.txt:wasn't found in this command\n$ error in the Rshell :in the otsreal.txtits not there\n",commandOut);

}

TEST(Output_RedirectTest,Output_RedirectCommand) {
  rShell runit;
  string commandline = "echo goat  >  text.txt";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell echo goat  >  text.txt:wasn't found in this command\n$ ",commandOut);

}


TEST(Double_RedirectTest,Double_RedirectCommand) {
  rShell runit;
  string commandline = "echo base stats  >>  next.txt";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell echo base stats  >>  next.txt:wasn't found in this command\n$ ",commandOut);

}


TEST(PipingTest,PipingCommand) {
  rShell runit;
  string commandline = "echo taking dubs | dubs.txt";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell echo taking dubs | dubs.txt:wasn't found in this command\n$ rshell dubs.txt:wasn't found in this command\n$ ",commandOut);

}

TEST(Combo_RedirectTest,Combo_RedirectCommand) {
  rShell runit;
  string commandline = "cat <  news.txt | echo nice watch";
  ::testing::internal::CaptureStdout();
  Command* comm = new Command();
  comm-> comm.push_back(commandline);
  EXPECT_FALSE(comm -> construct());
  runit.show();
  runit.parsing(commandline);
  runit.commandDesign();
  string commandOut = ::testing::internal::GetCapturedStdout();
  EXPECT_EQ("rshell cat <  news.txt | echo nice watch:wasn't found in this command\n$ error in the Rshell :in the otsnews.txtits not there\n",commandOut);

}
  
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}  
