using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Resources;

namespace SharedData
{
    public class SharedData
    {
        private readonly ResourceManager _manager;

        public SharedData()
        {
            _manager = new ResourceManager(
                string.Join('.', nameof(SharedData), "SharedData", "Generated"),
                GetType().Assembly); 
        }

        public IEnumerable<string> Resources()
        {
            foreach (DictionaryEntry entry in _manager.GetResourceSet(CultureInfo.CurrentUICulture, true, true))
            {
                yield return entry.Value as string;
            }
        }
        
    }
}