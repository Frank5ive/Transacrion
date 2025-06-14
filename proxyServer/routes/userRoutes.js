const express = require('express');
const router = express.Router();
const authController = require('../controller/authController');
const authMiddleware = require('../middleware/authMiddleware');

// Public routes
router.post('/login', authController.login);
router.post('/signup', authController.signup);

// Protected route example
router.get('/profile', authMiddleware, (req, res) => {
    res.json({ user: req.user });
});

module.exports = router;
