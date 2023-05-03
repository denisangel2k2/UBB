﻿
using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistency
{
    public interface IFlightRepository : IRepository<Flight>
    {
        void updateNumberOfSeats(int flightId);
    }
}
