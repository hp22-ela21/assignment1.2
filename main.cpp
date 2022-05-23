/* Inkluderingsdirektiv: */
#include <iostream>
#include <string>
#include <vector>

/************************************************************************************************
* Tilldelar osignerade heltal till tre variabler av datatypen size_t.
*************************************************************************************************/
static void assign(std::size_t* x, std::size_t* y, std::size_t* z)
{
   static std::size_t i = 0;
   *x = i++;
   *y = ++i * 2;
   *z = *x + *y;
   return;
}

/************************************************************************************************
* Skriver tre osignerade heltal till en specificerad utenhet, där standardutenhet stdout 
* används som default för utskrift i konsolen.
*************************************************************************************************/
static void print(std::FILE* stream, const std::size_t* x, const std::size_t* y, const std::size_t* z)
{
   if (!stream) stream = stdout;
   std::fprintf(stream, "x = %zu, y = %zu, z = %zu\n", *x, *y, *z);
   return;
}

/************************************************************************************************
* Skriver ut innehåll från en vektor innehållande text. I/O-strömmen är valbar.
*************************************************************************************************/
static void print(std::ostream* stream, const std::vector<std::string>* data)
{
   *stream << "--------------------------------------------------------------------------\n";
   for (auto i : *data)
      *stream << i << "\n";
   *stream << "--------------------------------------------------------------------------\n";
   return;
}

/************************************************************************************************
* Läser en rad med text från en given inström.
*************************************************************************************************/
static void readline(std::string* s, std::istream* stream = &std::cin)
{
   std::getline(*stream, *s);
   std::cout << "\n";
   return;
}

/************************************************************************************************
* Läser text från en given inström, lagrar varje inläst rad i en vektor, avslutar vid tom rad.
*************************************************************************************************/
static void read(std::istream* stream, std::vector<std::string>* data)
{
   std::string s;
   while (std::getline(*stream, s))
   {
      if (s == "") return;
      data->push_back(s);
   }
   return;
}

/************************************************************************************************
* Läser in data från konsolen och lagrar i en vektor. Inmatning sker tills användaren matar
* in en blank rad, då inläst innehåll skrivs ut innan funktionen avslutas.
*************************************************************************************************/
static void get_user_input(std::vector<std::string>* data, const std::string* username)
{
   std::cout << "Enter a sentence or a blank line to finish:\n";
   read(&std::cin, data);

   if (!data->size())
   {
      std::cout << "No sentences entered!\n";
   }
   else if (data->size() == 1)
   {
      std::cout << *username << ", you entered the following sentence:\n";
      print(&std::cout, data);
   }
   else
   {
      std::cout << *username << ", you entered the following " << data->size() << " sentences:\n";
      print(&std::cout, data);
   }
   return;
}

/************************************************************************************************
* Tilldelar osignerade tal till tre variabler x, y och z och skriver dessa till en textfil,
* följt av utskrift i konsolen. Förloppet repeteras fem gånger. Därefter sker inmatning av
* text från tangentbordet, vilket lagras i en strängvektor. När användaren matar in en blank
* rad så avslutas inmatningen och inmatat innehåll skrivs ut i konsolen.
*************************************************************************************************/
int main(void)
{
   std::FILE* fstream = std::fopen("data.txt", "w");
   std::size_t x, y, z;

   for (std::uint8_t i = 0; i < 5; i++)
   {
      assign(&x, &y, &z);
      print(fstream, &x, &y, &z);
      print(stdout, &x, &y, &z);
   }

   std::fclose(fstream);
   std::cout << "\nEnter your name:\n";
   std::string name;
   readline(&name);
   std::vector<std::string> data;
   get_user_input(&data, &name);
   return 0;
}
