"use strict";
const bcrypt = require("bcryptjs");
const jwt = require("jsonwebtoken");
const db = require("../models");

module.exports.login = async (req, res) => {
    const { username, password } = req.body;
    
    console.log('Login attempt for username:', username);
    
    if (!username || !password) {
        console.log('Login failed: Missing credentials');
        return res.status(400).json({ error: "Username and password are required" });
    }

    try {
        console.log('Searching for user in database...');
        const user = await db.User.findOne({ where: { username } });

        // Add more detailed logging
        if (!user) {
            console.log('Login failed: User not found');
            return res.status(401).json({ error: "Invalid credentials" });
        }

        const validPassword = await bcrypt.compare(password, user.passwordHash);
        if (!validPassword) {
            console.log('Login failed: Invalid password');
            return res.status(401).json({ error: "Invalid credentials" });
        }

        console.log('Login successful for user:', username);
        const token = jwt.sign(
            { id: user.id, username: user.username },
            process.env.JWT_SECRET,
            { expiresIn: "1h" }
        );
        res.json({ token });
    } catch (err) {
        console.error("Login error:", err);
        res.status(500).json({ error: "Internal server error" });
    }
}

module.exports.signup = async (req, res) => {
    const { username, password } = req.body;

    if (!username || !password) {
        return res.status(400).json({ error: "Username and password are required" });
    }

    try {
        const existingUser = await db.User.findOne({ where: { username } });
        if (existingUser) {
            return res.status(400).json({ error: "Username already exists" });
        }

        const salt = await bcrypt.genSalt(10);
        const passwordHash = await bcrypt.hash(password, salt);

        const user = await db.User.create({ username, passwordHash });
        res.status(201).json({ message: "User created", userId: user.id });
    } catch (err) {
        console.error("Signup error: ", err);
        res.status(500).json({ error: "Internal server error" });
    }
}