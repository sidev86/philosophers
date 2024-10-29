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
  <li>Taking a fork</li>
</ul>

<h3>Logging</h3>
<p>The program will log state changes in the following format:</p>
<pre>
  <code>
    timestamp_in_ms <span style="color:blue;">X</span> has taken a fork
    timestamp_in_ms <span style="color:blue;">X</span> <span style="color:red;">is</span> eating
    timestamp_in_ms <span style="color:blue;">X</span> <span style="color:red;">is</span> sleeping
    timestamp_in_ms <span style="color:blue;">X</span> <span style="color:red;">is</span> thinking
    timestamp_in_ms <span style="color:blue;">X</span> died
  </code>
</pre>
