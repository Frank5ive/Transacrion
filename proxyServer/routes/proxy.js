const express = require('express');
const proxy = require('express-http-proxy');

const router = express.Router();

// Debug all requests to this router
router.use((req, res, next) => {
  console.log('[PROXY ROUTER] Request:', req.method, req.originalUrl);
  console.log('[PROXY ROUTER] Path:', req.path);
  next();
});

// Simple proxy to C++ server
router.use('/', proxy('localhost:5000', {
  proxyReqOptDecorator: function(proxyReqOpts, srcReq) {
    console.log('=== PROXY REQUEST ===');
    console.log('Method:', srcReq.method);
    console.log('Path:', srcReq.path);
    console.log('Target:', 'localhost:5000' + srcReq.path);
    return proxyReqOpts;
  },
  
  userResDecorator: function(proxyRes, proxyResData, userReq, userRes) {
    console.log('=== PROXY RESPONSE ===');
    console.log('Status:', userRes.statusCode);
    return proxyResData;
  },
  
  proxyErrorHandler: function(err, res, next) {
    console.error('=== PROXY ERROR ===');
    console.error('Error:', err.message);
    res.status(500).json({ error: 'Proxy failed', message: err.message });
  }
}));

module.exports = router;