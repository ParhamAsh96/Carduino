@import '../assets/main.css';
<script setup></script>

<template>
  <main>
    <!--
    <div id="name">
      <h1>Carduino</h1>
    </div>
    -->
    <div id="guide">
      <ul>
        <li><img src="../pictures/test.png" alt="test" /></li>
        <li>
          <p>
            Lorem, ipsum dolor sit amet consectetur adipisicing elit. Sed
            eligendi explicabo saepe quidem assumenda corrupti culpa recusandae
            aliquam ut aspernatur, sit nisi! Ullam accusantium dolorum
            laboriosam explicabo, tenetur reprehenderit fugiat!
          </p>
        </li>
      </ul>
      <ul>
        <li><img src="../pictures/test.png" alt="test" /></li>
        <li>
          <p>
            Lorem, ipsum dolor sit amet consectetur adipisicing elit. Sed
            eligendi explicabo saepe quidem assumenda corrupti culpa recusandae
            aliquam ut aspernatur, sit nisi! Ullam accusantium dolorum
            laboriosam explicabo, tenetur reprehenderit fugiat!
          </p>
        </li>
      </ul>
      <ul>
        <li><img src="../pictures/test.png" alt="test" /></li>
        <li>
          <p>
            Lorem, ipsum dolor sit amet consectetur adipisicing elit. Sed
            eligendi explicabo saepe quidem assumenda corrupti culpa recusandae
            aliquam ut aspernatur, sit nisi! Ullam accusantium dolorum
            laboriosam explicabo, tenetur reprehenderit fugiat!
          </p>
        </li>
      </ul>
    </div>
  </main>
</template>

<style scoped>
/*
#name h1 {
  position: relative;
  color: rgb(217, 217, 217);
  text-align: center;
  margin-top: 10%;
}

#name:hover {
  color: #ffcc00;
}
*/

#guide {
  margin-top: 20vh;
  color: rgb(217, 217, 217);
  padding: 0 20vw;
  box-sizing: border-box;
}

#guide ul {
  display: flex;
  align-items: stretch;
  list-style: none;
  margin: 2vh 0;
  padding: 0;
  gap: 1rem;
  height: 20vh;
}

#guide li {
  flex: 0 0 25vw;
  box-sizing: border-box;
}

#guide li:first-child img {
  display: block;
  width: 100%;
  height: 100%;
  object-fit: contain;
}

#guide li:nth-child(2) p {
  margin: 0;
  overflow-wrap: break-word;
}
</style>
