#include <iostream>
#include <sstream>

class HashTable
{
private:
	static const int Size = 26;//�˴��ɲ���Ҫ�����ⲿ����const int HshTable::Size;

	struct Entry//�������ݺ�״̬��Ϣ
	{
		std::string Data;
		std::string Status = "never used!";//��ʼ״̬Ϊ��δʹ��
	};
public:
	HashTable() = default;

	void Add(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, index);
		
		if (exists)//��������ھ�ʲô������
			return;

		int insertIndex = GetInsertIndex(entryString);

		m_Entries[insertIndex].Data = entryString;
		m_Entries[insertIndex].Status = "occpuied!";
	}

	void Delete(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, index);

		if (!exists)//����������ھ�ʲô������
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
		return entryString.back() - 'a';//ȡ�����һ��Ԫ�أ��������һ��Ԫ����'a'����ô������������0
	}

	bool Find(const std::string& entryString, int& outIndex)
	{
		int index = GetIndex(entryString);//���ݼ���ȡ���±�

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
		int index = GetIndex(entryString);//���ݼ���ȡ���±�

		while (true)
		{
			if (m_Entries[index].Status == "never used!" || m_Entries[index].Status == "tombstone")
				return index;

			index = (index + 1) % Size;
		}

		return -1;
	}
private:
	Entry m_Entries[Size];//�ṹ������
};

int main()
{
	//����ʾ����Aapple Aorange Dapple Astrawberry
	//Ԥ�������orange strawberry
	std::string input;
	getline(std::cin, input);//��ȡһ�����룬�ᱣ���ո�

	HashTable hashTable;

	std::stringstream ss(input);//����һ���ַ�����������input�е����ݴ���
	while (ss.good())//����ַ�����ss��״̬�Ƿ���Ч�����Ƿ��пɶ�ȡ������
	{
		std::string token;//��ʱ�ַ���token
		ss >> token;//���ַ�����ss����ȡһ���Կո�ָ������ַ���������token
		//std::cout << token << std::endl;

		//ȡ���ӵڶ����ַ���ʼ�����ַ���
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