#include <iostream>
#include <locale.h>
#include <sstream> // Necessário para o nosso "to_string" manual
#include <vector> // No topo do código
#include <stdlib.h> // Necessário para o system()
#include <windows.h> // Adicione este include
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

		// Ajuste para colocar o '0' na frente se for menor que 10
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
	Data DataNascimento;

	// Função interna para limpar o número (essencial para o setTelefone funcionar)
	string limpar(string num)
	{
		string r = "";
		for (size_t i = 0; i < num.size(); i++)
		{
			if (isdigit(num[i])) r += num[i];
		}
		return r;
	}

public:
	Contato(string Email, string Nome, string Telefone, int dia, int mes, int ano)
		: Email(Email), Nome(Nome), DataNascimento(dia, mes, ano)
	{
		this->setTelefone(Telefone);
	}

	// Getters e Setters mantidos conforme solicitado
	void setEmail(string Email)
	{
		this->Email = Email;
	}
	string getEmail()
	{
		return Email;
	}

	void setNome(string Nome)
	{
		this->Nome = Nome;
	}
	string getNome()
	{
		return Nome;
	}

	void setTelefone(string numero)
	{
		string n = limpar(numero);
		if (n.size() == 11)
			Telefone = "(" + n.substr(0, 2) + ") " + n.substr(2, 5) + "-" + n.substr(7, 4);
		else if (n.size() == 10)
			Telefone = "(" + n.substr(0, 2) + ") " + n.substr(2, 4) + "-" + n.substr(6, 4);
		else
			Telefone = n;
	}
	string getTelefone()
	{
		return Telefone;
	}

	void setDataNascimento(int dia, int mes, int ano)
	{
		DataNascimento.setDia(dia);
		DataNascimento.setMes(mes);
		DataNascimento.setAno(ano);
	}
	Data getDataNascimento() const
	{
		return DataNascimento;
	}

	int calcularIdade(const Data& hoje)
	{
		int idade = hoje.getAno() - DataNascimento.getAno();
		if (hoje.getMes() < DataNascimento.getMes() ||
				(hoje.getMes() == DataNascimento.getMes() && hoje.getDia() < DataNascimento.getDia()))
		{
			idade--;
		}
		return idade;
	}

	void imprimir(const Data& hoje)
	{
		cout << "Nome: " << Nome << endl;
		cout << "Email: " << Email << endl;
		cout << "Telefone: " << Telefone << endl;
		cout << "Data de nascimento: " << DataNascimento.getData() << endl;
		cout << "Idade: " << calcularIdade(hoje) << endl;
	}
};



int main(int argc, char** argv)
{

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	setlocale(LC_ALL, ".UTF8");

	string nome;
	string email;
	string telefone;

	int contact = 0;
	int escolha;

	int x, y, z;

	vector<Contato> listaContatos;


	Data hoje(15, 8, 2026);

	while(contact < 6)
	{

		// Validação Nome
		while (true)
		{
			bool temNumero = false;
			cout << "Digite o Nome: ";
			getline(cin >> ws, nome);
			for (size_t i = 0; i < nome.size(); i++)
			{
				if (isdigit(nome[i])) temNumero = true;
			}
			if (!temNumero && nome.size() > 0) break;
			cout << "[ERRO] O nome nao pode conter numeros." << endl;
		}

		// Validação Email
		while (true)
		{
			cout << "Digite o Email: ";
			cin >> email;
			size_t atPos = email.find('@');
			size_t dotPos = email.find('.', atPos);
			if (atPos != string::npos && atPos > 0 && dotPos != string::npos && dotPos < email.size() - 1) break;
			cout << "[ERRO] Email invalido! Tente novamente." << endl;
		}

		// Validação Telefone
		while (true)
		{
			cout << "Telefone (DDD + Numero): ";
			cin >> telefone;
			string temp = "";
			for(size_t i = 0; i < telefone.size(); i++)
			{
				if(isdigit(telefone[i])) temp += telefone[i];
			}
			if (temp.size() == 10 || temp.size() == 11)
			{
				telefone = temp;
				break;
			}
			cout << "[ERRO] Digite 10 ou 11 numeros!" << endl;
		}

		// Substitua o loop "while(true)" da data por este:
		while(true)
		{
			char sep; // Para capturar a '/' ou o espaço
			cout << "Digite a data de nascimento (DD/MM/AAAA): ";

			// Lê o dia, pula um caractere, lê o mês, pula outro, lê o ano
			if (cin >> x >> sep >> y >> sep >> z)
			{
				// 1. Validar Ano
				if (z < 1900 || z > 2026)
				{
					cout << "[ERRO] Ano invalido!" << endl;
					continue;
				}

				// 2. Validar Mes
				if (y < 1 || y > 12)
				{
					cout << "[ERRO] Mes invalido!" << endl;
					continue;
				}

				// 3. Validar Dia (Considerando meses e bissexto)
				int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
				if ((z % 4 == 0 && z % 100 != 0) || (z % 400 == 0)) diasNoMes[1] = 29;

				if (x >= 1 && x <= diasNoMes[y - 1])
				{
					break; // Sucesso!
				}
				else
				{
					cout << "[ERRO] Dia invalido para o mes informado!" << endl;
				}
			}
			else
			{
				// Caso o usuário digite algo que não seja número
				cout << "[ERRO] Formato invalido! Use DD/MM/AAAA." << endl;
				cin.clear(); // Limpa o erro do cin
				cin.ignore(1000, '\n'); // Descarta a entrada ruim
			}
		}



		Contato c(email, nome, telefone , x, y, z);

		listaContatos.push_back(c);
		contact++;
		cout << "-----------------------" << endl;

		cout << "Digite 1 para adicionar um novo contato ou 0 para terminar" << endl;
		cin >> escolha;
		if(escolha == 0)
		{
			break;
		}
		system("cls");
	}

	system("cls");

	cout << "\n======= SUA AGENDA =======" << endl;

	for (int i = 0; i < listaContatos.size(); i++)
	{
		cout << "-----------------------" << endl;
		listaContatos[i].imprimir(hoje);
	}

	return 0;
}
