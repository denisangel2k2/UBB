using System;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace ZborCSharpRestClient
{
    class Program
    {
        private static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));
        private static string URL="http://localhost:8080/airline/flights";
        
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            RunAsync().Wait();
        }

        static async Task RunAsync()
        {
            client.BaseAddress = new Uri(URL);
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));
            
            int id = 1;
            Console.WriteLine("Get flight {0}", id);
            Flight result1 = await GetFlightAsync(URL+"/"+id);
            Console.WriteLine("Am primit {0},{1}", result1.Id,result1.Destination);
            
            //Create a flight
            Flight flight = new Flight{Id=99,Destination = "Bucuresti", Hour = "12:00", Date = "12.12.2019", NumberOfSeats = 100, AvailableSeats = 100};
            Flight result = await CreateFlightAsync(URL, flight);
            Console.WriteLine("Am primit {0},{1}", result.Id,result.Destination);
            int idd = result.Id;
            //Get all flights
            Console.WriteLine("Get all flights");
            Flight[] result2 = await GetAllFlightsAsync(URL);
            foreach (Flight f in result2)
            {
                Console.WriteLine("Am primit {0},{1}", f.Id,f.Destination);
            }
            
            //Update a flight
            Flight flightUpdated=await UpdateFlightAsync(URL+"/"+92,flight);
            Console.WriteLine("Am primit {0},{1}", flightUpdated.Id,flightUpdated.AvailableSeats);
            
            //Delete a flight
            var operation=DeleteFlightAsync(URL,result.Id);
            Flight[] result3 = await GetAllFlightsAsync(URL);
            foreach (Flight f in result3)
            {
                if (f.Id==idd)
                {
                    Console.WriteLine("Nu s-a sters");
                }
            }
            
            Console.WriteLine("S-a sters cu succes zborul cu id {0}",idd);

            
        }
        static async Task<Flight> GetFlightAsync(string path)
        {
            Flight flight = null;
            HttpResponseMessage response = await client.GetAsync(path);
            if (response.IsSuccessStatusCode)
            {
                flight = await response.Content.ReadAsAsync<Flight>();
            }
            return flight;
        }
        static async Task<Flight[]> GetAllFlightsAsync(string path)
        {
            Flight[] flights = null;
            HttpResponseMessage response = await client.GetAsync(path);
            if (response.IsSuccessStatusCode)
            {
                flights = await response.Content.ReadAsAsync<Flight[]>();
            }
            return flights;
        }
        
        static async Task<Flight> CreateFlightAsync(string path, Flight flight)
        {
            Flight result = null;
            HttpResponseMessage response = await client.PostAsJsonAsync(path, flight);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Flight>();
            }
            return result;
        }
        static async Task<Flight> DeleteFlightAsync(string path, int id)
        {
            Flight result = null;
            HttpResponseMessage response = await client.DeleteAsync(path+"/"+id);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Flight>();
            }
            return result;
        }
        
        static async Task<Flight> UpdateFlightAsync(string path, Flight flight)
        {
            Flight result = null;
            HttpResponseMessage response = await client.PutAsJsonAsync(path, flight);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Flight>();
            }
            return result;
        }

    }

    public class Flight
    {
        public int Id { get; set; }
        [JsonProperty("destination")]
        public string Destination { get; set; }
        [JsonProperty("date")]
        public string Date { get; set; }
        [JsonProperty("hour")]
        public string Hour { get; set; }
        [JsonProperty("numberOfSeats")]
        public int NumberOfSeats { get; set; }
        [JsonProperty("availableSeats")]
        public int AvailableSeats { get; set; }
    }
    public class LoggingHandler : DelegatingHandler
    {
        public LoggingHandler(HttpMessageHandler innerHandler)
            : base(innerHandler)
        {
        }
    
        protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
        {
            //Console.WriteLine("Request:");
            //Console.WriteLine(request.ToString());
            /*if (request.Content != null)
            {
                Console.WriteLine(await request.Content.ReadAsStringAsync());
            }*/
            //Console.WriteLine();
    
            HttpResponseMessage response = await base.SendAsync(request, cancellationToken);
    
            //Console.WriteLine("Response:");
            //Console.WriteLine(response.ToString());
            /*if (response.Content != null)
            {
                Console.WriteLine(await response.Content.ReadAsStringAsync());
            }*/
            //Console.WriteLine();
    
            return response;
        }
    }
}