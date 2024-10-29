<h1>Philosophers</h1>

<h2>Description</h2>

<p>The Philosophers project is a simulation of the classic Dining Philosophers problem, a well-known concurrency problem in computer science. The simulation involves multiple philosophers seated around a circular table with a bowl of spaghetti in the center and a fork placed between each pair of philosophers. Each philosopher alternates between thinking, eating, and sleeping, ensuring that no philosopher starves. The simulation is designed to explore synchronization and thread management using mutexes to control access to shared resources.</p>

<h2>Simulation Logic</h2>

Each philosopher is represented as a thread, and there is a mutex for each fork to prevent race conditions.
The simulation tracks the state of each philosopher, which can be:
<ul>
  <li>Taking a fork</li>
  <li>Eating</li>
  <li>Sleeping</li>
  <li>Thinking</li>
  <li>Dying (if they do not have a meal in the given time period)</li>
</ul>

<h3>Logging</h3>
<p>The program will log state changes in the following format:</p>
<pre><code>timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died</code></pre>

<ul>
  <li><code>timestamp_in_ms</code> should reflect the current timestamp in milliseconds.</li>
  <li><code>X</code>represents the philosopher number, which ranges from 1 to the total number of philosophers.</li>
  <li>Each log entry should be distinct, and death messages should be displayed no more than 10 ms after the event.</li>
</ul>

<h2>Compilation</h2>
Type <strong><code>make</code></strong> to compile and generate the <strong><code>philo</code></strong> executable file

<h2>Usage</h2>
<p>To run the simulation, execute the program with the required arguments:</p>
<pre><code><strong>./philo</strong> number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]</code></pre>

<p>For example:</p>
<pre><code><strong>./philo</strong> 5 800 200 200 3</code></pre>

<p>This command would simulate 5 philosophers who have 800 ms to eat before starving, take 200 ms to eat, and sleep for 200 ms, with a requirement of eating 3 times.</p>
<p><strong>Important note:</strong> The parameter <code>[number_of_times_each_philosopher_must_eat]</code> is optional. 
<ul>
  <li>When this optional parameter is specified, the simulation stops if all philosophers have eaten the number of times defined by this parameter, or if any philosopher dies of starvation before reaching that number of meals.</li>
  <li> If the optional parameter is not provided, the simulation may run indefinitely or may end with one of the philosophers starving, depending on the values entered by the user for the simulation.</li>
</ul></p>

