using System;
using System.Windows.Forms;
using System.Speech.Synthesis;
using System.Speech.Recognition;
using System.Diagnostics;
using System.IO.Ports;
using System.Xml;
using System.IO;

namespace AI_ASSISTANT
{

    public partial class Form1 : Form
    {

        private const string Format = "https://query.yahooapis.com/v1/public/yql?q=select * from weather.forecast where woeid in (select woeid from geo.places(1) where text='portland, or')&format=xml&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

        SpeechSynthesizer s = new SpeechSynthesizer();

        Boolean wake = false;

        SerialPort port = new SerialPort("COM3", 9600, Parity.None, 8, StopBits.One);

        //String temp;

        //String condition;

        string name = " Elmer";
        
        //Boolean var1 = false;

        Choices list = new Choices();

        //String namepath = @"";

        public Form1()
        {

            SpeechRecognitionEngine rec = new SpeechRecognitionEngine();

            //all words in word list bellow must begin with small letters not capital

            list.Add(new string[] 
            {

                "hello", "how are you?", "I'm fine too", "what is your name?", "what time is it?", "what is the date of today?", "open browser", /*"close browser",*/ "stop listening", "lia",
                "restart", "update", "light on", "light off", "open word", /*"close word",*/ /*"open unity",*/ /*"close unity",*/ "play", "pause",
                "enter", "start music", /*"close music",*/ "start movies", /*"close movies",*/ "where am I?", "what is happening today?", "how is the weather of today?", /*"what are the temperatures today?",*/ /*"tell me a joke",*/
                "minimize", "maximize", "close app", "next", "previous", "repeat", /*"what's my name?",*/ /*"what do I like?",*/ /*"what else?",*/ /*"search for",*/
                /*searching commands*/ /*"pro evolution",*/ /*"games", "computer",*/ /*"football",*/ "stop", "all commands", "show about"

            });

            //list.Add(File.ReadAllLines(@"C:\Program Files\LIA\Lia commands.txt"));

            Grammar gr = new Grammar(new GrammarBuilder(list));

            try
            {

                rec.RequestRecognizerUpdate();
                rec.LoadGrammar(gr);
                rec.SpeechRecognized += rec_SpeechRecognized;
                rec.SetInputToDefaultAudioDevice();
                rec.RecognizeAsync(RecognizeMode.Multiple);

            }

            catch
            {

                return;

            }

           /* public void say(String h)
            {

                s.Speak(h);
            
            }
           */

            s.SelectVoiceByHints(VoiceGender.Female);

            s.Speak("Hello, I'm Lia, and I will be happy to assist you");

            InitializeComponent();

        }

        public Boolean search = false;

        public static void KillProg(String s)
        {

            System.Diagnostics.Process[] procs = null;

            try
            {

                procs = Process.GetProcessesByName(s);

                Process prog = procs[0];

                if (!prog.HasExited)
                {

                    prog.Kill();

                }

            }

            catch
            {

                MessageBox.Show("Program was not open","ERROR");

            }

            finally
            {

                if (procs != null)
                {

                    foreach(Process p in procs)
                    {

                        p.Dispose();

                    }

                }

            }

            procs = null;

        }

        public void restart()
        {

            Process.Start(@"C:\Program Files (x86)\Terra Exploration\Lia Assistant\AI ASSISTANT.exe");
            Environment.Exit(0);

        }

        String[] greetings = new String[2] { "hi! good day", "hello! greetings"};

        String[] misunderstood = new String[2] { "sorry, I didn't get you, look at the command list if you are confused", "sorry, I didn't understand you, check the command list if you are confused"};

        String[] hobbies = new String[5] { "you like playing football", "Elmer, you like watching movies and animes", "Elmer, you like watching football", "playing video games is a big hobbie to you", "listening to music, from time to time"};

        public String greetings_action()
        {

            Random r = new Random();
            return greetings[r.Next(2)];

        }

        public String hobbies_action()
        {

            Random r = new Random();
            return hobbies[r.Next(5)];

        }

        public String misunderstood_action()
        {

            Random r = new Random();
            return misunderstood[r.Next(2)];

        }

        private void rec_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {

            String r = e.Result.Text;

            if (r == "lia") wake = true; //when command lia is given boolean sets to true

            if (r == "lia") //command given by user
            {

                say("Yes"); //response gotten from system
                label7.Text = "CURRENT STATE: ACTIVE";
                say("I'm listening");

            }

            if (r == "stop listening") wake = false;

            if (r == "stop listening")
            {

                say("Logging you out");
                label7.Text = "CURRENT STATE: INACTIVE";
                say("I am currently inactive, all commands will be overruled");

            }

            if (r == "stop")
            {

                s.SpeakAsyncCancelAll();

            }

            if (search)
            {

                Process.Start("https://www.google.com/search?sxsrf="+r);
                search = false;

            }

            //list of commands

            if (wake == true && search == false)
            {
                if (r == "show about")
                {

                    say("showing about");
                    Process.Start("https://terraexploration.space/terra-exploration-information-technology-about/");
                    say("website launched");

                }

                else

                /*if (r != "hello" || r != "how are you?" || r != "I'm fine too" || r != "what is your name?" || r != "what time is it?" ||
                    r != "what is the date of today?" || r != "open browser(to open default browser)" || r != "stop listening" ||
                    r != "lia" || r != "restart" || r != "update" || r != "light on(to turn light on)" || r != "light off" ||
                    r != "open word" || r != "play" || r != "pause" || r != "enter" || r != "start music" ||
                    r != "start movies" || r != "where am I?" || r != "what is happening today?" || r != "how is the weather of today?" ||
                    r != "minimize" || r != "maximizer" || r != "close app" || r != "next" || r != "previous" ||
                    r != "repeat" || r != "stop" || r != "all commands" || r != "terra x")
                {

                    say(misunderstood_action());

                }*/

                if (r == "search for")
                {

                    search = true;

                }

                else

                /*if (r=="tell me a joke")
                {

                    say(w.DownloadString("http://api.yomomma.info/").Replace("\"", "").Replace("{", "").Replace("}", "").Replace(":", "").Replace("joke", ""));
                
                }*/

                if (r == "what do I like?" || r == "what else?")
                {

                    say(hobbies_action());

                }

                else

                if (r == "what's my name?")
                {

                    say("Your name is" + name);

                }

                else

                if (r == "minimize")
                {

                    this.WindowState = FormWindowState.Minimized;

                }

                else

                if (r == "maximize")
                {

                    this.WindowState = FormWindowState.Normal;

                }

                else

                if (r == "what is happening today?")
                {

                    Process.Start("bingnews://");

                }

                else

                if (r == "where am I?")
                {

                    Process.Start("bingmaps://");

                }

                else

                if (r == "how is the weather of today?")
                {

                    //say("the weather is" + GetWeather("cond") + ".");
                    Process.Start("bingweather://");

                }

                else

                /*if (r == "what are the temperatures today?")
                {

                    say("temperature is" + GetWeather("temp") + "degrees.");
                
                }*/

                if (r == "light on") //what user says
                {

                    say("turning the light on"); //response from pc 
                    serialPort1.Open();
                    serialPort1.WriteLine("A");
                    serialPort1.Close();
                    say("light is currently on");

                }

                else

                if (r == "light off")
                {

                    say("turning the light off");
                    serialPort1.Open();
                    serialPort1.WriteLine("B");
                    serialPort1.Close();
                    say("light is currently off");

                }

                else

                //command

                if (r == "open word")
                {

                    //response

                    say("opening word");
                    Process.Start(@"C:\Program Files (x86)\Microsoft Office\root\Office16\WINWORD.EXE");
                    say("word launched");

                }

                else

                if (r == "close word")
                {

                    say("exiting word");
                    KillProg("WINWORD");
                    say("word exited");

                }

                else

                if (r == "restart" || r == "update")
                {

                    say("restarting");
                    restart();

                }

                else

                if (r == "hello")
                {

                    say(greetings_action());

                }

                else

                if (r == "how are you?")
                {

                    say("I'm fine, and you?");

                }

                else

                if (r == "I'm fine too")
                {

                    say("very well, how may I help you?");

                }

                else

                if (r == "what is your name?")
                {

                    say("I aready said it, my name is Lia");

                }

                else

                if (r == "what time is it?")
                {

                    say(DateTime.Now.ToString("h:mm tt"));

                }

                else

                if (r == "what is the date of today?")
                {

                    say(DateTime.Now.ToString("M/d/yyyy"));

                }

                else

                if (r == "open browser")
                {

                    say("opening your default browser");
                    Process.Start("Http://google.com");
                    say("browser launched");

                }

                else

                /*if (r == "close browser")
                {

                    say("exiting opera browser");
                    KillProg("Opera");
                    say("opera browser exited");
                
                }*/

                if (r == "open unity")
                {

                    say("opening unity");
                    Process.Start(@"C:\Program Files\Unity\Hub\Editor\2017.4.35f1\Editor\Unity.exe");
                    say("unity launched");

                }

                else

                /*if (r == "close unity")
                {

                    say("exiting unity");
                    KillProg("Unity");
                    say("unity exited");
                
                }*/

                if (r == "start music")
                {

                    say("loading sound tracks");
                    //how to open microsoft apps (don't give any space befor or after brackets)
                    Process.Start("mswindowsmusic://"); 
                    say("music player launched");

                }

                else

                /*if (r == "close music")
                 {

                     say("exiting music player");
                     KillProg("Groove Music");
                     say("music player exited");

                 }*/

                if (r == "start movies")
                {

                    say("loading movies and videos");
                    Process.Start("mswindowsvideo://");
                    say("video player launched");

                }

                else

                /*if (r == "close movies")
                {

                    say("exiting video player");
                    KillProg("microsoft.zunevideo_10.19101.10711.0_x64__8wekyb3d8bbwe");
                    say("video player exited");
                
                }*/

                if (r == "play" || r == "pause")
                {

                    SendKeys.Send(" ");

                }

                else

                if (r == "enter")
                {

                    SendKeys.Send("{ENTER}");

                }

                else

                if (r == "close app")
                {

                    say("stopping ongoing process");
                    SendKeys.Send("%{F4}");
                    say("process terminated");

                }

                else

                //use samll letters when making in app (e.g groove music) shortcuts 

                if (r == "next")
                {

                    SendKeys.Send("^(f)");

                }

                else

                if (r == "previous")
                {

                    SendKeys.Send("^(b)");

                }

                else

                if (r == "repeat")
                {

                    SendKeys.Send("^(b)");

                }

                else

                if (r == "all commands")
                {

                    say("opening commands list");
                    Process.Start(@"C:\Program Files (x86)\Terra Exploration\Lia Assistant\Lia commands.txt");
                    say("command list launched");

                }

                else

                if (r == "about")
                {

                    say("showing about");
                    Process.Start("https://terraexploration.space");
                    say("website launched");

                }
                
            }

            richTextBox1.AppendText(r + "\n");

        }

        private void say(object p)
        {

            throw new NotImplementedException();

        }

        /*public String GetWeather(String input)
        {

            string query = string.Format(Format);
            XmlDocument wData = new XmlDocument();
            try
            {

                wData.Load(query);
            
            }
            
            catch
            {

                MessageBox.Show("No Internet Connection","ERROR");
                return "No Internet Connection";
            
            }

            XmlNamespaceManager manager = new XmlNamespaceManager(wData.NameTable);
            manager.AddNamespace("yweather", "http://xml.weather.yahoo.com/ns/rss/1.0");

            XmlNode channel = wData.SelectSingleNode("query").SelectSingleNode("results").SelectSingleNode("channel");
            XmlNodeList nodes = wData.SelectNodes("query/results/channel");
            
            try
            {

                temp = channel.SelectSingleNode("item").SelectSingleNode("yweather:condition", manager).Attributes["temp"].Value;
                condition = channel.SelectSingleNode("item").SelectSingleNode("yweather:condition", manager).Attributes["text"].Value;
                
                if (input == "temp")
                {

                    return temp;
                
                }
             
                if (input == "cond")
                {

                    return condition;
                
                }
            
            }

            catch
            {

                return "Error Reciving data";
            
            }
            
            return "error";
        
            }*/

        public void say(String h)
        {
            
            //s.Speak(h);

            s.SpeakAsync(h);
            richTextBox2.AppendText(h + "\n");

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void bunifuFlatButton1_Click(object sender, EventArgs e)
        {

            wake = true;
            say("Signing you in");
            label7.Text = "CURRENT STATE: ACTIVE";
            say("I am currently active, all commands will be validated");

        }

        private void bunifuFlatButton2_Click(object sender, EventArgs e)
        {

            wake = false;
            say("Logging you out");
            label7.Text = "CURRENT STATE: INACTIVE";
            say("I am currently inactive, all commands will be overruled");

        }

        private void aBOUTToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Console.Beep(1000, 300);
            say("showing about");
            Process.Start("https://terraexploration.space/terra-exploration-information-technology-about/");
            say("website launched");

        }

        private void aLLCOMMANDSToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Console.Beep(1000, 300);
            say("opening command list");
            Process.Start(@"C:\Program Files (x86)\Terra Exploration\Lia Assistant\Lia commands.txt");
            say("command list launched");

        }

        private void mENUToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Console.Beep(1000,300);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            int num1;
            int num2;
            Random rnd = new Random();
            num1 = rnd.Next(10000, 100000);
            num2 = rnd.Next(10000, 100000);
            label2.Text = Convert.ToString(num1);
            label8.Text = Convert.ToString(num2);

        }

        private void bunifuFlatButton3_Click(object sender, EventArgs e)
        {

            say("stopping all processes");
            say("restarting");
            restart();

        }

        private void bunifuFlatButton4_Click(object sender, EventArgs e)
        {

            say("stopping all processes");
            say("shutting down");
            SendKeys.Send("%{F4}");

        }
    }

}