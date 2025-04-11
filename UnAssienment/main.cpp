#include <iostream>
#include <sstream>

class HashTable
{
private:
	static const int Size = 26;//此处可不需要再在外部定义const int HshTable::Size;

	struct Entry//保存数据和状态信息
	{
		std::string Data;
		std::string Status = "never used!";//初始状态为从未使用
	};
public:
	HashTable() = default;

	void Add(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, index);
		
		if (exists)//如果键存在就什么都不做
			return;

		int insertIndex = GetInsertIndex(entryString);

		m_Entries[insertIndex].Data = entryString;
		m_Entries[insertIndex].Status = "occpuied!";
	}

	void Delete(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, index);

		if (!exists)//如果键不存在就什么都不做
			return;

		m_Entries[index].Status = "tombstone!";
	}

	void Print()
	{
		for (int i = 0; i < Size; i++)
		{
			if(m_Entries[i].Status == "occpuied!")
				std::cout << m_Entries[i].Data << ' ';
		}
		std::cout << std::endl;
	}
private:
	int GetIndex(const std::string& entryString)
	{
		return entryString.back() - 'a';//取出最后一个元素，例如最后一个元素是'a'，那么他的索引就是0
	}

	bool Find(const std::string& entryString, int& outIndex)
	{
		int index = GetIndex(entryString);//根据键获取的下标

		while (true)
		{
			if (m_Entries[index].Data == entryString)
			{
				outIndex = index;
				return true;
			}

			if (m_Entries[index].Status == "never used!")
				return false;

			index = (index + 1) % Size;
		}

		return false;
	}

	int GetInsertIndex(const std::string& entryString)
	{
		int index = GetIndex(entryString);//根据键获取的下标

		while (true)
		{
			if (m_Entries[index].Status == "never used!" || m_Entries[index].Status == "tombstone")
				return index;

			index = (index + 1) % Size;
		}

		return -1;
	}
private:
	Entry m_Entries[Size];//结构体数组
};

int main()
{
	//输入示例：Aapple Aorange Dapple Astrawberry
	//预期输出：orange strawberry
	std::string input;
	getline(std::cin, input);//获取一行输入，会保留空格

	HashTable hashTable;

	std::stringstream ss(input);//创建一个字符串流，并将input中的内容传入
	while (ss.good())//检查字符串流ss的状态是否有效，即是否还有可读取的内容
	{
		std::string token;//临时字符串token
		ss >> token;//从字符串流ss中提取一个以空格分隔的子字符串，存入token
		//std::cout << token << std::endl;

		//取出从第二个字符开始的子字符串
		//std::string entryName = token.substr(1);
		std::string entryString = &token[1];
		if (token[0] == 'A')
			hashTable.Add(entryString);
		else if (token[0] == 'D')
			hashTable.Delete(entryString);
	}

	hashTable.Print();

	return 0;
}