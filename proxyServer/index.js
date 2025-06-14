const express = require("express");
require("dotenv").config();
const db = require("./models");

const app = express();
app.use(express.json());

// Routes
app.use("/auth", require("./routes/userRoutes"));
app.use("/proxy", require("./routes/proxy"));

// Connect DB and Start Server
db.sequelize.sync().then(() => {
  const PORT = process.env.PORT || 3000;
  app.listen(PORT, () => {
    console.log(`🚀 Proxy server running on http://localhost:${PORT}`);
  });
});
