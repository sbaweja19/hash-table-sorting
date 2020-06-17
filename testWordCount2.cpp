#include <iostream>
#include <sstream>
#include "WordCount.h"
#include "tddFuncs.h"

using namespace std;

int main()
{
	ASSERT_EQUALS("monkeys", WordCount::makeValidWord("-2mOnkEYs-$"));
	

	WordCount a;
	a.incrWordCount("hello");

	ASSERT_EQUALS(1, a.getWordCount("hello"));
	ASSERT_EQUALS(1, a.getNumUniqueWords());

	a.incrWordCount("hello-");

	ASSERT_EQUALS(2, a.getWordCount("hello"));
	ASSERT_EQUALS(1, a.getNumUniqueWords());

	a.incrWordCount("bob");

	ASSERT_EQUALS(2, a.getWordCount("hello"));
	ASSERT_EQUALS(1, a.getWordCount("bob"));
	ASSERT_EQUALS(2, a.getNumUniqueWords());
	ASSERT_EQUALS(3, a.getTotalWords());

	a.decrWordCount("hello");

	ASSERT_EQUALS(1, a.getWordCount("hello"));
	ASSERT_EQUALS(1, a.getWordCount("bob"));
	ASSERT_EQUALS(2, a.getNumUniqueWords());

	a.decrWordCount("hello");
	a.decrWordCount("bob");

	ASSERT_EQUALS(0, a.getWordCount("hello"));
	ASSERT_EQUALS(0, a.getWordCount("bob"));
	ASSERT_EQUALS(0, a.getNumUniqueWords());

	a.addAllWords("My name is Sanil- is my name");
	/*a.incrWordCount("my");
	a.incrWordCount("my");
	a.incrWordCount("is");
	a.incrWordCount("is");
	a.incrWordCount("name");
	a.incrWordCount("name");
	a.incrWordCount("sanil");*/

	ostringstream out;
	ostringstream expected;
	expected << "is,2\nmy,2\nname,2\nsanil,1\n";
	a.dumpWordsSortedByWord(out);

	ASSERT_EQUALS(expected.str(), out.str());

	ostringstream out2;
	ostringstream expected2;
	expected2 << "sanil,1\nis,2\nmy,2\nname,2\n";
	a.dumpWordsSortedByOccurence(out2);
	ASSERT_EQUALS(expected2.str(), out2.str());

	return 0;
}
