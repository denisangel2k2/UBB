using Microsoft.Data.SqlClient;
namespace ConsoleApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            
            Console.WriteLine("Monty este baiat salajean");
            try
            {
                string connectionString = @"Server=LAPTOP-RI290K7P\SQLEXPRESS;
                Database=Seminar1SGBD2242023; 
                Integrated Security=true;
                TrustServerCertificate=true;";
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    
                    Console.WriteLine("Starea conexiunii: {0}",connection.State);
                    connection.Open();
                    Console.WriteLine("Starea conexiunii: " + connection.State);
                    SqlCommand insertCommand = new SqlCommand("INSERT INTO Flori (nume,pret,sezon) VALUES " + "(@nume,@pret,@sezon);", connection);
                    insertCommand.Parameters.AddWithValue("@nume", "lalea");
                    insertCommand.Parameters.AddWithValue("@pret", 7.0F);
                    insertCommand.Parameters.AddWithValue("@sezon", "primavara");
                    int rowCount=insertCommand.ExecuteNonQuery();
                    Console.WriteLine("Insert Row Count Flori: "+ rowCount);
                    SqlCommand selectCommandFlori = new SqlCommand("select nume, pret, sezon from Flori;", connection);
                    SqlDataReader reader=selectCommandFlori.ExecuteReader();
                    if (reader.HasRows)
                    {
                        Console.WriteLine("citirea datelor din flori");
                        while (reader.Read())
                        {
                            Console.WriteLine("{0}\t{1}\t{2}",reader.GetString(0), reader.GetFloat(1), reader.GetString(2));
                        }
                        
                    }
                    reader.Close();
                }
            }
            catch (Exception ex)
            {

                Console.Error.WriteLine(ex.ToString());
                
            }
        }
    }
}