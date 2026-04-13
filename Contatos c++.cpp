#include <iostream>
#include <vector>
#include <sstream>
#include <windows.h>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include <cctype>



using namespace std;

template <typename T>
string to_string(T value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

class Data
{
private:
	int dia;
	int mes;
	int ano;

public:
	Data(int dia, int mes, int ano)
	{
		this->dia = dia;
		this->mes = mes;
		this->ano = ano;
	}

	Data()
	{
		this->dia = 0;
		this->mes = 0;
		this->ano = 0;
	}

	void setDia(int dia)
	{
		this->dia = dia;
	}
	void setMes(int mes)
	{
		this->mes = mes;
	}
	void setAno(int ano)
	{
		this->ano = ano;
	}

	int getDia() const
	{
		return this->dia;
	}
	int getMes() const
	{
		return this->mes;
	}
	int getAno() const
	{
		return this->ano;
	}

	string getData()
	{
		string sdia = to_string(this->dia);
		string smes = to_string(this->mes);
		string sano = to_string(this->ano);

		if (sdia.size() < 2) sdia.insert(0, 1, '0');
		if (smes.size() < 2) smes.insert(0, 1, '0');

		return sdia + "/" + smes + "/" + sano;
	}

};


class Contato
{
private:
	string Email;
	string Nome;
	string Telefone;
	int dia;
	int mes;
	int ano;
	Data dtnasc;

	int idade;

public:
	void setNome(const string& n)
	{
		Nome = n;
	}

	string getNome()
	{
		return Nome;
	}

	void setEmail(const string& e)
	{
		Email = e;
	}

	string getEmail()
	{
		return Email;
	}

	void setTelefone(const string& t)
	{
		Telefone = t;
	}

	string getTelefone()
	{
		return Telefone;
	}

	void SetDataNascimento(int d, int m, int a)
	{

		dtnasc.setDia(d);
		dtnasc.setMes(m);
		dtnasc.setAno(a);
	}

	string GetDataNascimento()
	{
		return dtnasc.getData();
	}

	void CalcIdade(int ano)
	{
		idade = 2026 - ano;
	}


	void Imprimir()
	{
		cout << "Nome: " << Nome << endl;
		cout << "Email: " << Email << endl;

		cout << "Telefone:(" << Telefone.substr(0, 2) << ")"
			 << Telefone.substr(2, 5) << "-" << Telefone.substr(6, 4) << endl;

		cout << "Data de Nascimento: " << dtnasc.getData() << endl;
		cout << "Idade: " << idade << endl;
	}
};

bool isValidEmail(string email)
{

	size_t atPos = email.find('@');

	size_t dotPos = email.find_last_of('.');

	if (atPos != string::npos && atPos > 0 &&
			dotPos != string::npos && dotPos > atPos + 1 &&
			dotPos < email.length() - 1)
	{
		return true;
	}
	return false;
}

bool temNumeros(std::string nome)
{
	for (size_t i = 0; i < nome.length(); i++)
	{
		if (isdigit(static_cast<unsigned char>(nome[i])))
		{
			return true;
		}
	}
	return false;
}

int main()
{


	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	setlocale(LC_ALL, ".UTF8");

	string nome;
	string email;
	string telefone;

	int x, y, z;

	int pessoas = 1;

	vector<Contato> listaContatos;

	while(pessoas <= 5)
	{
		int Escolha;

		Contato p;

		while(true)
		{
			cout << "Digite o Nome:";
			cin >> nome;
			
			if(temNumeros(nome))
			{
				cout << "O nome não deve conter números!" << endl;
			}
			else
			{
				break;
			}
		}

		while(true)
		{
			cout << "Digite o Email:";
			cin >> email;
			if (isValidEmail(email))
			{
				break;
			}

			else
			{
				cout << "[ERRO] Email em formato invalido! Tente novamente." << endl;
			}
		}

		while(true)
		{
			cout << "Digite o Telefone: ";
			cin >> telefone;

			bool soNumeros = true;
			for(size_t i = 0; i < telefone.length(); i++)
				if(!isdigit(telefone[i])) soNumeros = false;

			if(!soNumeros)
			{
				cout << "[ERRO] Digite apenas numeros!" << endl;
				continue;
			}
			if(telefone.length() < 10 || telefone.length() > 11)
			{
				cout << "[ERRO] Telefone precisa ter 10 ou 11 digitos!" << endl;
				continue;
			}
			break;
		}

		while (true)
		{
			cout << "Digite o dia do nascimento: ";
			if (!(cin >> x))  
			{
				cout << "[ERRO] Digite apenas numeros!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}

			cout << "Digite o mes do nascimento: ";
			if (!(cin >> y))
			{
				cout << "[ERRO] Digite apenas numeros!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}

			cout << "Digite o ano do nascimento: ";
			if (!(cin >> z))
			{
				cout << "[ERRO] Digite apenas numeros!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}


			if (z < 1900 || z > 2026)
			{
				cout << "[ERRO] Ano invalido (1900-2026)!" << endl;
				continue;
			}

			if (y < 1 || y > 12)
			{
				cout << "[ERRO] Mes invalido (1-12)!" << endl;
				continue;
			}


			int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


			if ((z % 4 == 0 && z % 100 != 0) || (z % 400 == 0))
			{
				diasNoMes[1] = 29;
			}

			if (x >= 1 && x <= diasNoMes[y - 1])
			{
		
				break;
			}
			else
			{
				cout << "[ERRO] Dia " << x << " invalido para o mes " << y << "!" << endl;
			}
		}

		p.setNome(nome);
		p.setEmail(email);
		p.setTelefone(telefone);
		p.SetDataNascimento(x, y, z);
		p.CalcIdade(z);

		listaContatos.push_back(p);
		pessoas++;

		if(pessoas < 5)
		{
			cout << "Digite 1 para adicionar um novo contato ou 0 para terminar" << endl;
			cin >> Escolha;

			cin.ignore(1000, '\n');

			if(Escolha == 0)
			{
				break;
			}

		}
		system("cls");
		Sleep(500);
	}

	system("cls");

	cout << "\n======= SUA AGENDA =======" << endl;

	for(int i = 0; i < listaContatos.size(); i++)
	{
		listaContatos[i].Imprimir();
		cout << "-----------------------" << endl;
	}

	return 0;
}




